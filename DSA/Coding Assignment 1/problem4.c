#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE 1024
#define MAX_RECORDS 1000
#define P 4294967291U // Prime number used for hashing

typedef struct {
    int key;
    char name[100];
    char email[100];
    char gender[11];
} person;

typedef struct {
    unsigned int a, b; // Parameters for the second-level hash function
    int size; // Size of second-level hash table
    person **table; // Array of pointers to people
} SecondLevel;

typedef struct {
    unsigned int a, b; // Parameters for first-level hash function
    int m; // Size of first-level hash table
    SecondLevel *buckets; // Array of pointers pointing to second-level hash tables
} HashTable;

// Hash function: universal hashing
unsigned int hash(unsigned int a, unsigned int b, int key, int m) {
    if (m == 0) return 0;
    return ((unsigned long long)a * (unsigned long long)key + (unsigned long long)b) % P % m;
}

// Helper function: sum of squares of array elements
static int square_sum(int *arr, int n) {
    int result = 0;
    for (int i = 0; i < n; i++)
        result += arr[i] * arr[i];
    return result;
}

void buildSecondLevel(SecondLevel *sl, int *keys, int l, person *people, int n) {
    if (l == 0) {
        sl->size = 0;
        sl->table = NULL;
        sl->a = 0;
        sl->b = 0;
        return;
    }

    int size_h2 = 10 * l * l;
    sl->table = NULL;
    sl->a = 0;
    sl->b = 0;
    sl->size = size_h2;

    unsigned int a2, b2;
    int attempts = 0;
    const int MAX_ATTEMPTS = 100000; // To avoid an infinite loop

    do {
        if (sl->table) free(sl->table);
        sl->table = calloc(size_h2, sizeof(person *));
        if (!sl->table) {
            fprintf(stderr, "Memory allocation failed for second-level table\n");
            exit(EXIT_FAILURE);
        }

        a2 = rand() % P;
        b2 = rand() % P;

        int *occupied = calloc(size_h2, sizeof(int));
        if (!occupied) {
            fprintf(stderr, "Memory allocation failed for occupied array\n");
            free(sl->table);
            exit(EXIT_FAILURE);
        }

        int collision = 0;
        for (int i = 0; i < l; i++) {
            int idx = hash(a2, b2, keys[i], size_h2);
            if (occupied[idx]) {
                collision = 1;
                break;
            }
            occupied[idx] = 1;
        }
        if (collision) {
            free(occupied);
            attempts++;
            continue;
        }

        // Place people in second-level table
        for (int i = 0; i < l; i++) {
            int idx = hash(a2, b2, keys[i], size_h2);
            for (int j = 0; j < n; j++) {
                if (people[j].key == keys[i]) {
                    sl->table[idx] = &people[j];
                    break;
                }
            }
        }
        free(occupied);
        break;

    } while (attempts < MAX_ATTEMPTS);

    if (attempts == MAX_ATTEMPTS) {
        fprintf(stderr, "Failed to build perfect second-level hash after %d attempts\n", MAX_ATTEMPTS);
        free(sl->table);
        sl->table = NULL;
        sl->size = 0;
    } else {
        sl->a = a2;
        sl->b = b2;
    }
}

// Build the two-level perfect hash table
void buildHashTable(HashTable *ht, person *people, int n, int m) {
    if (!ht || !people || n <= 0 || m <= 0) return;

    int *keys = malloc(n * sizeof(int));
    if (!keys) {
        fprintf(stderr, "Memory allocation failed for keys\n");
        exit(EXIT_FAILURE);
    }
    // Obtain the keys
    for (int i = 0; i < n; i++)
        keys[i] = people[i].key;

    ht->m = m;
    ht->buckets = calloc(m, sizeof(SecondLevel));
    if (!ht->buckets) {
        fprintf(stderr, "Memory allocation failed for first-level buckets\n");
        free(keys);
        exit(EXIT_FAILURE);
    }

    int attempts = 0;
    const int MAX_ATTEMPTS = 100000;

    int *collision_count = calloc(m, sizeof(int)); // An array to store numbers of collisions
    // A 2D array to store the keys according to first-level hashing, i.e. storing the keys with the same h1 value in the same row
    int **collided_keys = malloc(m * sizeof(int *)); 
    for (int i = 0; i < m; i++)
        collided_keys[i] = malloc(n * sizeof(int));

    do {
        for (int i = 0; i < m; i++)
            collision_count[i] = 0;

        ht->a = rand() % P;
        ht->b = rand() % P;

        for (int i = 0; i < n; i++) {
            int h1 = hash(ht->a, ht->b, keys[i], m);
            collided_keys[h1][collision_count[h1]++] = keys[i];
        }

        int sum = square_sum(collision_count, m);
        if (sum <= 5 * n)
            break;

        attempts++;
    } while (attempts < MAX_ATTEMPTS);

    if (attempts == MAX_ATTEMPTS) {
        fprintf(stderr, "Could not create a perfect first-level hash in %d attempts\n", MAX_ATTEMPTS);
        free(keys);
        for (int i = 0; i < m; i++)
            free(collided_keys[i]);
        free(collided_keys);
        free(collision_count);
        free(ht->buckets);
        ht->buckets = NULL;
        return;
    }

    // Build second-level hash tables
    for (int i = 0; i < m; i++) {
        buildSecondLevel(&ht->buckets[i], collided_keys[i], collision_count[i], people, n);
    }

    free(keys);
    for (int i = 0; i < m; i++)
        free(collided_keys[i]);
    free(collided_keys);
    free(collision_count);
}

// Search for a person in the hash table
person* lookup(HashTable *ht, int key) {
    if (!ht || ht->m == 0) return NULL;

    int h1 = hash(ht->a, ht->b, key, ht->m);
    SecondLevel *sl = &ht->buckets[h1];

    if (sl->size == 0 || sl->table == NULL)
        return NULL;

    int h2 = hash(sl->a, sl->b, key, sl->size);
    person *p = sl->table[h2];

    if (p && p->key == key)
        return p;
    else
        return NULL;
}

// Free the memory used by the hash table
void freeHashTable(HashTable *ht) {
    if (!ht) return;
    for (int i = 0; i < ht->m; i++) {
        free(ht->buckets[i].table);
    }
    free(ht->buckets);
}

#define MAX_LINE_LEN 1024

// A helper function for reading the CSV file
// Function to trim newline or trailing spaces from string
void trim_newline(char *str) {
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r' || str[len - 1] == ' ')) {
        str[len - 1] = '\0';
        len--;
    }
}

// Reads CSV file and returns dynamically allocated array of person structs.
// Sets *count to number of records read or -1 on error.
person* readCSV(const char *filename, int *count) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open CSV file");
        *count = -1;
        return NULL;
    }

    char line[MAX_LINE_LEN];
    int capacity = 1000;  // initial capacity
    person *people = malloc(capacity * sizeof(person));
    if (!people) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        *count = -1;
        return NULL;
    }

    int idx = 0;
    // Skip header line (if your CSV has a header)
    if (fgets(line, sizeof(line), fp) == NULL) {
        fprintf(stderr, "Empty file or read error\n");
        fclose(fp);
        free(people);
        *count = -1;
        return NULL;
    }

    while (fgets(line, sizeof(line), fp)) {
        trim_newline(line);
        // CSV format: S.No.,Key (NHS No.),First_Name,Email,Gender
        // We want Key (2nd), First_Name(3rd), Email(4th), Gender(5th)
        char *token;
        char *rest = line;
        int col = 0;

        person p;

        // Parse fields by comma
        while ((token = strtok_r(rest, ",", &rest))) {
            col++;
            if (col == 2) {  // Key
                p.key = atoi(token);
            } else if (col == 3) {  // First Name
                strncpy(p.name, token, sizeof(p.name));
                p.name[sizeof(p.name) - 1] = '\0';
            } else if (col == 4) {  // Email
                strncpy(p.email, token, sizeof(p.email));
                p.email[sizeof(p.email) - 1] = '\0';
            } else if (col == 5) {  // Gender
                strncpy(p.gender, token, sizeof(p.gender));
                p.gender[sizeof(p.gender) - 1] = '\0';
            }
        }

        if (idx >= capacity) {
            capacity *= 2;
            person *tmp = realloc(people, capacity * sizeof(person));
            if (!tmp) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(people);
                fclose(fp);
                *count = -1;
                return NULL;
            }
            people = tmp;
        }

        people[idx++] = p;
    }

    fclose(fp);
    *count = idx;
    return people;
}

int main() {
    srand((unsigned)time(NULL));

    int n;
    person *people = readCSV("Dictionary Data.csv", &n);

    HashTable ht;
    buildHashTable(&ht, people, n, 5 * n);

    int query_key;
    while (1) {
        printf("Enter key to search or -1 to quit: ");
        if (scanf("%d", &query_key) != 1)
            break;
        if (query_key == -1)
            break;

        person *result = lookup(&ht, query_key);
        if (result) {
            printf("Found: %s, %s, %s\n", result->name, result->email, result->gender);
        } else {
            printf("Key %d not found\n", query_key);
        }
    }

    freeHashTable(&ht);
    return 0;
}
