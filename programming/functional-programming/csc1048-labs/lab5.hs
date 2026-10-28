import Control.Monad (when)
-- CSC1048 Computability and Complexity
-- Functional Programming Lab 5: Abstract Data Types and Higher-order Functions

-- Rust's analog:
-- #[derive(Debug, PartialEq, Eq, PartialOrd, Ord, Debug)] -- with std::fmt::Dispaly implementation
-- enum BinTree {
--     Empty,
--     Root({ left: BinTree, right: BinTree})
-- }
data BinTree t = Empty | Root t (BinTree t) (BinTree t)
                 deriving (Eq, Ord, Show)

myTree = Root 5 (Root 1 (Empty) (Root 3 Empty Empty)) (Root 7 Empty Empty)

leaf :: t -> BinTree t
leaf x = Root x (Empty) (Empty)

myTree1 = Root 5 (Root 1 (Empty) (leaf 3)) (leaf 7)

addNode :: (Ord a) => a -> (BinTree a) -> (BinTree a)
addNode x Empty = leaf x
addNode x (Root val left right)
    | (x < val) = Root val (addNode x left) (right)
    | (x > val) = Root val (left) (addNode x right)
    | otherwise = Root val left right

makeTree :: (Ord a) => [a] -> BinTree a
makeTree [] = Empty
makeTree (x:xs) = addNode x (makeTree xs)

inOrderTraversal :: (Ord a) => BinTree a -> [a]
inOrderTraversal Empty = []
inOrderTraversal (Root val left right) = inOrderTraversal left ++ [val] ++ inOrderTraversal right

monkeyPuzzleSort :: (Ord a) => [a] -> [a]
monkeyPuzzleSort xs = inOrderTraversal (makeTree xs)

higherOrderSort :: (a -> a -> Bool) -> [a] -> [a]
higherOrderSort _ [] = []
higherOrderSort rel (x:xs) = insert x (higherOrderSort rel xs)
    where
        insert y [] = [y]
        insert y (z:zs)
            | rel y z = y : z : zs
            | otherwise = z : insert y zs
