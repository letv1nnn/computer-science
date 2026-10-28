-- CSC1048 Computability and Complexity
-- Functional Programming Lab 2: Defining Functions

-- 1. Area of a Triangle
triangleArea :: Float -> Float -> Float -> Float
triangleArea a b c = sqrt (s * (s - a) * (s - b) * (s - c))
    where s = (a + b + c) / 2

-- 2. Sum Test
isSum :: (Num a, Eq a) => a -> a -> a -> Bool
isSum x y z
    | x == y + z = True
    | y == x + z = True
    | z == x + y = True
    | otherwise = False

-- 3. Area of a Triangle (revisited)
validTriangle :: (Num a, Ord a) => a -> a -> a -> Bool
validTriangle a b c
    | a >= b && a >= c && a < (b + c) = True
    | b >= a && b >= c && b < (a + c) = True
    | c >= a && c >= b && c < (a + b) = True
    | otherwise = False

triangleArea' :: Float -> Float -> Float -> Float
triangleArea' a b c
    | validTriangle a b c = sqrt (s * (s - a) * (s - b) * (s - c))
    | otherwise = error "triangle is not valid"
    where s = (a + b + c) / 2
