import Control.Applicative (Alternative(empty))
-- CSC1048 Computability and Complexity
-- Functional Programming Lab 4: More Recursion and Lists

myAppend :: [a] -> [a] -> [a]
myAppend [] ys = ys
myAppend (x:xs) ys = x:(myAppend xs ys)

myHead :: [a] -> a
myHead (x:xs) = x

myLast :: [a] -> a
myLast [] = error "empty list"
myLast [x] = x 
myLast (_:xs) = myLast xs

myTail :: [a] -> [a]
myTail (_:xs) = xs 

myInit :: [a] -> [a]
myInit [] = error "empty list"
myInit [x] = []
myInit (x:xs) = x:myInit xs

myLength :: [a] -> Int
myLength [] = 0
myLength (_:xs) = 1 + myLength xs

myReverse :: [a] -> [a]
myReverse [] = []
myReverse (x:xs) = myReverse xs ++ [x]

mySum :: (Num a) => [a] -> a
mySum [] = 0
mySum (x:xs) = x + mySum xs

myProduct :: (Num a) => [a] -> a
myProduct [] = error "list is empty"
myProduct [x] = x
myProduct (x:xs) = x * myProduct xs

myMaximum :: (Ord a) => [a] -> a
myMaximum [] = error "list is empty"
myMaximum [x] = x
myMaximum (x:xs) = let big = myMaximum xs in
                    if x > big then x else big

myMinimum :: (Ord a) => [a] -> a
myMinimum [] = error "list is empty"
myMinimum [x] = x
myMinimum (x:xs) = let small = myMinimum xs in
                    if x < small then x else small

myElem :: (Eq a) => a -> [a] -> Bool
myElem _ [] = False
myElem x (y:ys) = if x == y then True
                   else myElem x ys

myElem' :: (Eq a) => a -> [a] -> Bool
myElem' x xs = not (null [True | y <- xs, y == x])

myDelete :: (Eq a) => a -> [a] -> [a]
myDelete _ [] = []
myDelete x (y:ys) = if x == y then ys
                     else y:(myDelete x ys)

myUnion :: (Eq a) => [a] -> [a] -> [a]
myUnion x [] = x 
myUnion x (y:ys) = if myElem y x then myUnion x ys
                    else myUnion (x  ++ [y]) ys

myDescribeList :: [a] -> String
myDescribeList xs = "The list is " ++ what xs 
    where what [] = "empty."
          what [x] = "a singleton list."
          what xs = "a longer list."
