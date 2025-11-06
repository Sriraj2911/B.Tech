(*1. Tail of a list*)
let rec last_element= function
| [] -> None
| [x] -> x
| h :: t -> last_element t

(*2. Last two elements of a list*)
let rec last_two = function
| [] -> None
| [x] -> None
| [x ; y] -> Some (x, y)
| _ :: _ :: t -> last_two t

(*3. N'th element of a list*)
let rec at n lst = 
  match lst with
  | [] -> None
  | h :: t ->
    if n<0 then None
    else if n=0 then Some h
    else at (n-1) t

(*4. Length of a list*)
let rec length = function
  | [] -> 0
  | h :: t -> 1 + length t

(*5. Reverse a list*)
let rec rev = function
  | [] -> []
  | h :: t -> rev t @ [h]

(*6. Palindrome*)
let is_palindrome lst = 
  (*Using the list reversal from the previous problem*)
  lst = rev lst

(*7. Run-length encoding*)
let encode lst =
  let rec aux count acc = function
    |[] -> []
    | [x] -> (count+1, x) :: acc
    | a :: (b :: _ as t) -> if a=b then aux (count + 1) acc t
                            else aux 0 ((count + 1, a) :: acc) t in
  List.rev (aux 0 [] lst);;

(*8. Duplicate the elements of a list*)
let rec duplicate = function
  | [] -> []
  | h :: t -> [h ; h] @ duplicate t

(*9. Split a list into two parts; The length of the first part is given*)
let split lst n = 
  let rec aux i acc = function
    | [] -> List.rev acc, []
    | h :: t as l -> if i=0 then List.rev acc, l
                            else aux (i-1) (h :: acc) t
  in
    aux n [] lst;;

(*10. Remove the K'th element from a list*)
let rec remove_at k lst = 
  match lst with
    | [] -> []
    | h :: t -> if k = 0 then t
                else h :: (remove_at (k-1) t)
