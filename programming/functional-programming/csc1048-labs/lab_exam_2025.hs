-- CSC1048 Computability & Complexity
-- Haskell Lab Exam

-- Q1. Write an expression that evaluates to a list of the even 
-- numbers that are a multiple of 9 and less than 300.
q1 :: (Integral a) => [a]
q1 = [x | x <- [0..299], x `mod` 2 == 0, x `mod` 9 == 0]

-- Q2. Write a function that takes two integers and evaluates 
-- to a list of integers between the first integer and the second
-- integer, including the first and second integers. If the first
-- number is greater than the second number, the returned list
-- should be empty.
q2 :: (Integral a) => a -> a -> [a]
q2 l r
  | l > r = []
  | otherwise = [x | x <- [l..r]]

-- Q3. Write a function, diff, that takes two lists and returns
-- a list that is all the elements of the first list that are not
-- in the second list, 
-- e.g. diff [1, 2, 3, 5, 6, 7] [2, 4, 6, 8] evaluates to [1, 3, 5, 7]
diff :: (Eq a) => [a] -> [a] -> [a]
-- diff xs ys = [x | x <- xs, x `notElem` ys] -- no recursion
diff [] _ = []
diff (x:xs) ys
  | x `elem` ys = diff xs ys
  | otherwise = x : diff xs ys

-- Q4.GHC Write a data type for a binary tree.
data BinTree t = Empty | Root t (BinTree t) (BinTree t)
                 deriving (Eq, Ord, Show)

-- Q5. Write a function that converts a binary tree into a list
-- by doing a preorder traversal of the binary tree. Remember a
-- preorder traversal visits the parent node, then the left child
-- and then the right node.
preorderTraversal :: BinTree a -> [a]
preorderTraversal Empty = []
preorderTraversal (Root val left right) =
  val : preorderTraversal left ++ preorderTraversal right

-- additionally, other traversals
inorderTraversal :: BinTree a -> [a]
inorderTraversal Empty = []
inorderTraversal (Root val left right) =
  inorderTraversal left ++ [val] ++ inorderTraversal right

postorderTraversal :: BinTree a -> [a]
postorderTraversal Empty = []
postorderTraversal (Root val left right) =
  postorderTraversal left ++ postorderTraversal right ++ [val]


