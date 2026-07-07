-- basic typeclasses
-- `Eq` is used for types that support equality testing (==, /=).
-- (==) :: (Eq a) => a -> a -> Bool
--
-- `Ord` is for types that have an ordering (<, >, <=, >=).
-- (>) :: (Ord a) => a -> a -> Bool
-- `compare` is a function that returns Ordering (EQ, GT, LT)
--
-- `Show` can be presented as strings.
-- `show` takes a Show member and presents it as a string
--
-- `Read` is sort of the opposite typeclass of `Show`.
-- `read` takes a string and returns a type which is a member of `Read`
--
-- `Enum` members are sequentially ordered types, they can be enumerated.
-- Its members can be used in list ranges (defined successors and predecessors).
--
-- `Bounded` members have an upper and a lower bound.
-- defines `minBound` and `maxBound`
--
-- `Num` is a numeric typeclass, its members have the property of being able to act like numbers.
-- To join `Num`, a type must already be friends with `Show` and `Eq`.
--
-- `Integral` is also a numeric typeclass (includes both real and integral numbers).
-- `Floating` includes only floating point numbers, so Float and Double
-- fromIntegral :: (Num b, Integral a) => a -> b

squareAll :: (Num a) => [a] -> [a]
squareAll lst = map (\x -> x ^ 2) lst

showAll :: (Show a) => [a] -> [String]
showAll lst = map (\el -> show el) lst

keep :: (Eq a) => a -> [a] -> [a]
keep el lst = filter (\x -> x == el) lst

longerThanFour :: [String] -> [String]
longerThanFour lst = filter (\s -> (length s) > 4) lst

doubleEvenNumbers :: (Integral a) => [a] -> [a]
doubleEvenNumbers nums = map (\x -> x * 2) (filter (\x -> x `mod` 2 == 0) nums)

unique :: Eq a => [a] -> [a]
unique [] = []
unique (x:xs) = x : unique (filter (/= x) xs)

positiveStrings :: [Int] -> [String]
positiveStrings nums = map (\x -> show x) (filter (\x -> x > 0) nums)

