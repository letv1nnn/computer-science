-- cons list implementation

data List x = Nil | Cons x (List x)
  deriving Show

fromList :: [a] -> List a
fromList [] = Nil
fromList (x:xs) = Cons x (fromList xs) 

toList :: List a -> [a]
toList Nil = []
toList (Cons val rest) = val : toList rest

len :: List a -> Integer
len Nil = 0
len (Cons _ rest) = 1 + len rest

headL :: List a -> Maybe a
headL Nil = Nothing
headL (Cons val _) = Just val

tailL :: List a -> Maybe a
tail Nil = Nothing
tailL (Cons val Nil) = Just val
tailL (Cons _ rest) = tailL rest

append :: List a -> List a -> List a
append Nil l = l
append (Cons x xs) ys = Cons x (append xs ys)

rev :: List a -> List a
rev Nil = Nil
rev (Cons x xs) = append (rev xs) (Cons x Nil)

mapL :: (a -> b) -> List a -> List b
mapL _ Nil = Nil
mapL f (Cons x xs) = Cons (f x) (mapL f xs)

filterL :: (a -> Bool) -> List a -> List a
filterL _ Nil = Nil
filterL p (Cons x xs)
  | p x = Cons x (filterL p xs)
  | otherwise = filterL p xs

