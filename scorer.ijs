
runs =: 3 : 0 "1 0 1 
+/ 3 4 5 runs y
:
y =. /:~ y
NB. TODO: run through and find each run
)

fifteens =: 3 : 0 "1

)

pairs =: 3 : 0 "1
NB. make sure there are 5 cards per hand
assert. 5 = $y
NB. sort y
y =. /:~ y
count =. 0
NB. rotate y as long as it is not the original list
orig =. y
whilst. -. y -: orig do.
    NB. check to see if the first 2 are the same.
    NB. count =. count + =/ 2 {. y NB. doesn't work for 3 of a kind
    oak =. <: +/ y = {. y
    count =. count + oak
    y =. (>:oak) |. y
end.
count return.
)
