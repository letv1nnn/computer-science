
-- `where` bindings are a syntactic construct that let you bind 
-- to variables at the end of a function and the whole function
-- can see them, including all the guards.
--
-- `let` bindings let you bind to variables anywhere and are 
-- expressions themselves, but are very local, so they don’t 
-- span across guards
--
-- The difference is that `let` bindings are expressions themselves.
-- `where` bindings are just syntactic constructs.

densityTell :: (RealFloat a) => a -> a -> String  
densityTell mass volume  
    | density < air = "Wow! You're going for a ride in the sky!"  
    | density <= water = "Have fun swimming, but watch out for sharks!"  
    | otherwise   = "If it's sink or swim, you're going to sink."  
    where density = mass / volume  
          air = 1.2  
          water = 1000.0  

max' :: (Ord a) => a -> a -> a
max' x y
    | x > y = x
    | otherwise = y
-- max' :: (Ord a) => a -> a -> a
-- max' a b | a > b = a | otherwise = b

myCompare :: (Ord a) => a -> a -> Ordering
x `myCompare` y
    | x > y = GT
    | x == y = EQ
    | otherwise = LT

initials :: String -> String -> String
initials firstname lastname = [f] ++ ", " ++ [l] ++ "."
    where (f:_) = firstname
          (l:_) = lastname

calcDensities :: (RealFloat a) => [(a, a)] -> [a]
calcDensities xs = [density m v | (m, v) <- xs]
    where density mass volume = mass / volume

cylinderArea :: (RealFloat a) => a -> a -> a
cylinderArea r h =
    let sideArea = 2 * pi * r * h
        topArea = 2 * pi * r
    in sideArea + 2 * topArea

