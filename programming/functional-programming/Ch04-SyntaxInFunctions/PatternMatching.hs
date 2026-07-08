
lucky :: (Integral a) => a -> String
lucky 7 = "LUCKY NUMBER 7!"
lucky _ = "Sorry, you're out of luck, pal"

addVector :: (Num a) => (a, a) -> (a, a) -> (a, a)
addVector (x1, y1) (x2, y2) = (x1 + x2, y1 + y2)

head' :: [a] -> a
head' [] = error "Can't call head on an empty list, dummy!"
head' (x:_) = x

second :: [a] -> a
second (_:y:_) = y
second _ = error "Can't call second on a list of length less than 2, dummy!"

length' :: [a] -> Int
length' [] = 0
length' (_:xs) = 1 + length' xs

sum' :: (Num a) => [a] -> a
sum' [] = 0
sum' (x:xs) = x + sum' xs

