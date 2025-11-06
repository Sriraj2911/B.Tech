let x =
  match not true with
  | true -> "nope"
  |false -> "yep"

let z = 
  match "foo" with
  |"hell" -> 0
  |_ -> 1

let artist = 
  match ["Taylor";"Swift"] with
  |[] -> "huh"
  | h :: t -> h 

let fst3 t = 
  match t with
  | (a, b, c) -> a

let rec sum lst = 
  match lst with
  | [] -> 0
  | h :: t -> h + sum t