(*1. Eliminate duplicates*)
let rec compress = function
| a :: (b :: _ as t) -> if a=b then compress t else a :: compress t
| [x] -> [x]
|[] -> []

(*2. Pack consecutive duplicates*)
let rec pack = function
  | []-> []
  | h :: t ->
      let same, rest = List.partition ((=) h) t in
      (h :: same) :: pack rest

(*This is a supporting function for the next problem*)
let rec add ele lst n =
  match n with
    | 0 -> lst
    | n -> add ele (ele :: lst) (n-1)
(*3. Replicate the elements of a list a given number of times*)
let rec replicate lst n = 
  match lst with
    | [] -> []
    | [x] -> add x [x] (n-1)
    | h :: t -> (add h [] n) @ replicate t n

(*4. Drop every N'th element from a list*)
let drop list n =
  let rec aux i = function
    | [] -> []
    | h :: t -> if i = n then aux 1 t else h :: aux (i + 1) t  in
  aux 1 list

(*5. Rotate a list N places to the left*)
let rec rotate lst n = 
  match lst with
    |[] -> []
    |[x] -> [x]
    | h :: t -> if n=0 then lst else rotate (t @ [h]) (n-1)
