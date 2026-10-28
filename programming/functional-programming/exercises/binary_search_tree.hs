-- binary search tree implementation
-- compile with `ghc binary_search_tree.hs`

data BinSearchTree x = Empty | Root x (BinSearchTree x) (BinSearchTree x)
  deriving Show

leaf :: a -> BinSearchTree a
leaf x = Root x Empty Empty

-- if a node is a leaf node
isLeaf :: BinSearchTree a -> Bool
isLeaf (Root _ Empty Empty) = True
isLeaf _ = False

-- pushes x to a bst
push :: (Ord a) => a -> BinSearchTree a -> BinSearchTree a
push x Empty = leaf x
push x (Root val left right)
  | x < val = Root val (push x left) right
  | x > val = Root val left (push x right)
  | otherwise = Root val left right

-- removes specific eleemnt from bst
pop :: (Ord a) => a -> BinSearchTree a -> BinSearchTree a
pop x Empty = Empty
pop x (Root val left right)
  | x < val = Root val (pop x left) right
  | x > val = Root val left (pop x right)
  | otherwise = case (left, right) of
      (Empty, _) -> right
      (_, Empty) -> left
      _ -> case minVal right of
          Just m -> Root m left (pop m right)
          Nothing -> left

-- minimual value
minVal :: (Ord a) => BinSearchTree a -> Maybe a
minVal Empty = Nothing
minVal (Root val Empty _) = Just val
minVal (Root _ left _) = minVal left

-- maximum value
maxVal :: (Ord a) => BinSearchTree a -> Maybe a
maxVal Empty = Nothing
maxVal (Root val _ Empty) = Just val
maxVal (Root _ _ right) = maxVal right

inorderTraversal :: BinSearchTree a -> [a]
inorderTraversal tree = case tree of
  Empty -> []
  Root val left right -> inorderTraversal left ++ [val] ++ inorderTraversal right

postorderTraversal :: BinSearchTree a -> [a]
postorderTraversal Empty = []
postorderTraversal (Root val left right) = postorderTraversal left ++ postorderTraversal right ++ [val]

preorderTraversal :: BinSearchTree a -> [a]
preorderTraversal tree = case tree of
  Empty -> []
  Root val left right -> val : preorderTraversal left ++ preorderTraversal right

-- creates a tree from a list
fromList :: (Ord a) => [a] -> BinSearchTree a
fromList [] = Empty
fromList (x:xs) = push x (fromList xs)

-- size of the bst
size :: BinSearchTree a -> Integer
size Empty = 0
size (Root _ left right) = 1 + size left + size right

-- get element by `idx` in the inorder traversed bst
get :: Int -> BinSearchTree a -> Maybe a
get _ Empty = Nothing
get idx tree
  | length sorted < idx = Nothing
  | otherwise = Just (sorted !! idx)
  where sorted = inorderTraversal tree

-- sort list using bst, converts list to bst and then inorder traverses
sortList :: (Ord a) => [a] -> [a]
sortList xs = inorderTraversal (fromList xs)

-- prints inorder
printSorted :: (Show a, Ord a) => BinSearchTree a -> IO ()
printSorted tree = print (inorderTraversal tree)

main :: IO ()
main = do
  putStrLn "Creating a binary search tree from [5, 3, 2, 4, 1]"
  let tree = fromList [5, 3, 2, 4, 1]
  printSorted tree

  putStrLn "Erased 3 from the BST"
  printSorted (pop 3 tree)

  putStrLn "Appended 42 to the BST"
  printSorted (push 42 tree)
  
  putStrLn ("Size of the initial BST: " ++ (show (size tree)))
  
  putStrLn ("Max element of the initial BST: " ++ (show (maxVal tree)))
  putStrLn ("Min elemenet of the initial BST: " ++ (show (minVal tree)))

  print "In-order, pre-order and post-order traversals of the initial BST"
  print (inorderTraversal tree)
  print (preorderTraversal tree)
  print (postorderTraversal tree)

