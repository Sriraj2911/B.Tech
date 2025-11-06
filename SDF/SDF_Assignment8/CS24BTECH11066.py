#!/usr/bin/env python3

#Problem 1
def steps(n):
    if(n==2):
        return 1
    else:
        if(n%2 == 0):
            return 1 + steps(n/2)
        else:
            return 1 + steps(3*n + 1)


#Problem 2
def reverse_line(text_file):
    with open(text_file, "r") as file:
        text = file.read()

    reversed_text = text[::-1]
    
    with open("reverse_lines_op.txt", "w") as file:
        file.write(f"{reversed_text}\n")


#Problem 3
def word_count(text_file):
    line_count = 0
    words = []
    chars = 0
    with open(text_file, "r") as file:
        for line in file:
            line_count += 1
            words += line.split()
            if line.rstrip("\n"):
                chars += len(line)
    unique_words = list(set(words))

    print(f"Number of character (including whitespace): {chars}")
    print(f"Number of words (separated by whitespace): {len(words)}")
    print(f"Number of lines: {line_count}")
    print(f"Number of unique words: {len(unique_words)}")

word_count("wcfile.txt")

#Problem 4
def dictdiff(d1, d2):
    d3 = {}
    for key in d1:
        if key in d2:
            if(d1[key] != d2[key]):
                d3[key] = [d1[key], d2[key]]
        else:
            d3[key] = [d1[key], None]
    for key in d2:
        if key not in d1:
            d3[key] = [None, d2[key]]
    return d3


#Problem 5
PEOPLE = [{'first':'Narendra', 'last':'Modi', 'email':'naren@modi.co.in'}, 
        {'first':'Donald', 'last':'Trump', 'email':'president@whitehouse.gov'}, 
        {'first':'Vladimir', 'last':'Putin', 'email':'president@kremvax.ru'}]

def alphabetize_names():
    result = sorted(PEOPLE, key=lambda person: (person['last'], person['first']))
    return result


#Problem 6
def most_repeating_word(string):
    words = string.split()
    alpha_count = [0] * 26
    arr = []
    max_list = []

    for word in words:
        alpha_count = [0] * 26
        #Counting the number of times a character has appeared in a word
        for char in list(word):
            alpha_count[ord(char)-ord('a')] += 1
        #Appending as a tuple to retain the relation between the word and its most repeated letter 
        arr.append((word, max(alpha_count)))
        #Creating a list of all the maximum letter counts in each word
        max_list.append(max(alpha_count))
    
    #Finding the most repeated letter
    max_count = max(max_list)
    #Finding the index of the most repeated letter
    index = max_list.index(max_count)

    return (words[index])


#Problem 7
def format_sort_records(PEOPLE):
    total = len(PEOPLE)
    for i in range(total):
        print(f'{(PEOPLE[i])[0]} {(PEOPLE[i])[1]} {round((PEOPLE[i])[2], 2)}')


#Problem 8
def passwd_to_dict(passwd_file):
    id = {}
    with open(passwd_file, "r") as file:
        for line in file:
            lst = line.split(":")
            id[lst[0]] = int(lst[2])
    return id


#Problem 9
def gematria_for(word):
    code = {chr(x+97): (x+1) for x in range(26)}
    result = 0
    for letter in word:
        if(not letter.islower()):
            return 0
        result += code[letter]
    return result


def gematria_equal_words(word):
    DICT_WORDS = ["cat", "bat", "act", "tap", "pat", "rat", "tar", "art", "zap", "ax", "fox", "box"]
    result = []
    for ele in DICT_WORDS:
        if(gematria_for(word) == gematria_for(ele)):
            result.append(ele)
    return result


#Problem 10
import random

def create_password_generator(string):
    pool = list(string)
    def random_password(length):
        return ''.join(random.choices(pool, k=length))
    return random_password


#Problem 11
class Circle:
    def __init__(self, string, number):
        self.string = string
        self.number = number
    def CircleIterator(self):
        array = list(self.string)
        array1 = array * (self.number)
        result = []
        for i in range(self.number):
            result.append(array1[i])
        return " ".join(map(str, result))


#Problem 12
class Animal:
    def __init__(self, color, legs):
        self.color = color
        self.legs = legs

    def __str__(self):
        return f"Animal (Color: {self.color}, Legs: {self.legs})"

class Cage:
    def __init__(self, cage_id):
        self.cage_id = cage_id
        self.animals = []

    def add_animal(self, animal):
        self.animals.append(animal)

    def __str__(self):
        animal_details = "\n ".join(str(animal) for animal in self.animals)
        return f"Cage {self.cage_id} contains:\n {animal_details if animal_details else 'No animal'}"

class Zoo:
    def __init__(self):
        self.cages = []

    def add_cage(self, cage):
        self.cages.append(cage)

    def filter_by_color(self, color):
        result = [animal for cage in self.cages for animal in cage.animals if animal.color == color]
        return result
    
    def filter_by_legs(number_of_legs):
        result = [animal for cage in self.cages for animal in cage.animals if animal.legs == legs]
        return result
    
    def total_legs(self):
        result = sum(animal.legs in cage in self.cages for animal in cage.animals)
        return result

    def __str__(self):
        result = "\n".join(str(cage) for cage in self.cages)
        return result


#Problem 13
import numpy as np

def pi_limit(n):
    if(n > 15):
        print("The maximum limit is 15 digits of precision after the decimal.")
        return pi_limit(15)
    return round(np.pi, n)


#Problem 14
def substring(string):
    result = []
    length = len(string)

    for i in range(length-1):
        for j in range(i+1, length):
            result.append(string[i:j])

    #Removing the substrings with more than two distinct letters
    for substr in result:
        if(len(set(substr)) > 2):
            result.remove(substr)
    
    lengths = []

    #Making a list of lengths of the substrings
    for substr in result:
        lengths.append(len(substr))
    
    max_length = max(lengths)

    return f"{max_length} {result[lengths.index(max_length)]}"


#Problem 15
def consecutive_sublist(array):
    num_set = set(array)
    result = []

    for num in array:
        #Checking for the start of the sublist
        if (num-1) not in num_set:
            num1 = num
            temp = []
            while num1 in num_set:
                temp.append(num1)
                num1 += 1
        if len(temp) > len(result):
            result = temp
    
    return result


