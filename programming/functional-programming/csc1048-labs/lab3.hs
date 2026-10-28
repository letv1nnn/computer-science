-- CSC1048 Computability and Complexity
-- Functional Programming Lab 3: Lists

-- 1. Palindromes
isPalindrome :: (Eq a) => [a] -> Bool
isPalindrome xs = xs == reverse xs

-- 2. Shortest list
shortest :: (Eq a) => [[a]] -> [a]
shortest [x] = x
shortest (x:xs) = if length x < length (shortest xs)
                  then x 
                  else shortest xs

-- 3. Adding Two Polynomials
type Poly = [Float]

addPolies :: Poly -> Poly -> Poly
addPolies xs ys = [x + y | (x, y) <- zip (xs ++ replicate (length ys - length xs) 0)
										 (ys ++ replicate (length xs - length ys) 0)]

addPolies' :: Poly -> Poly -> Poly
addPolies' xs [] = xs 
addPolies' [] ys = ys 
addPolies' (x:xs) (y:ys) = (x + y):(addPolies' xs ys)

-- 4. Evaluating a Polynomial
evalPoly :: Float -> Poly -> Float
evalPoly _ [el] = el
evalPoly x (p:ps) = p + (x * (evalPoly x ps))
