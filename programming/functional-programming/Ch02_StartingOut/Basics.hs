
doubleMe x = x * 2
tripleMe x = x * 3
square x = x * x
cube x = (square x) * x
average x y = (x + y) / 2.0

doubleThenSquare x = square(doubleMe x)
cubeAverage x y = cube(average x y)

isPositive x = x > 0
isEven x = if mod x 2 == 0 then True else False
describeNumber x
    | x == 0       = "zero"
    | isPositive x = "positive"
    | otherwise    = "negative"

