type primary_color = Red | Green | Blue

let r = Red

type point = float * float

type shape = 
  | Circle of {center : point; radius : float}
  | Rectangle of {upper_left : point; bottom_right : point}
