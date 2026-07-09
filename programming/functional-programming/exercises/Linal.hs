module Linal where

-- =============================================================================
-- LINEAR ALGEBRA EXERCISES
-- =============================================================================

vectorDim :: [Double] -> Int
vectorDim [] = 0
vectorDim (v:vs) = 1 + vectorDim vs 

zeroVector :: Int -> [Double]
zeroVector n
    | n < 0 = error "number of elements must be positive"
    | n == 0 = []
    | otherwise = 0:zeroVector (n - 1)

basisVector :: Int -> Int -> [Double]
basisVector n i
    | i < 0 = error "index must by greater than or equal to zero"
    | otherwise = [if j == i then 1.0 else 0.0 | j <- [1..n]]

vectorAdd :: [Double] -> [Double] -> [Double]
vectorAdd v u
    | length v /= length u = error "dimension mismatch"
    | otherwise = [vi + ui | (vi, ui) <- zip v u]

vectorSub :: [Double] -> [Double] -> [Double]
vectorSub [] [] = []
vectorSub (v:vs) (u:us) = (v - u):vectorSub vs us
vectorSub _ _ = error "dimension mismatch"

scalarMul :: Double -> [Double] -> [Double]
scalarMul s v = [ s * x | x <- v ]

dotProduct :: [Double] -> [Double] -> Double
dotProduct v u
    | length v /= length u = error "dimension mismatch"
    | otherwise = sum [ a1 * a2 | (a1, a2) <- zip v u ]

sameDim :: [a] -> [b] -> Bool
sameDim v u = length v == length u

vectorNorm :: (Floating a) => [a] -> a
vectorNorm v = sqrt (sum [ x ^ 2 | x <- v ])

normalizeVec :: [Double] -> [Double]
normalizeVec v
    | norm == 0.0 = v
    | otherwise = [ a / norm | a <- v ] 
    where norm = vectorNorm v

vectorDist :: [Double] -> [Double] -> Double
vectorDist v u
    | length v /= length u = error "dimension mismatch"
    | otherwise = sqrt (sum [ (a1 - a2) ^ 2 | (a1, a2) <- zip v u ])

vectorAngle :: [Double] -> [Double] -> Double
vectorAngle v u
    | length v /= length u = error "dimension mismatch"
    | otherwise = acos ( dotProduct v u / (vectorNorm v * vectorNorm u) )

-- =============================================================================
-- PART 3: PATTERN MATCHING & GUARDS (Ch04 — Syntax in Functions)
-- =============================================================================

-- | Cross product of two 3D vectors. Use pattern matching on the lists.
-- >>> crossProduct [1,0,0] [0,1,0]
-- [0.0,0.0,1.0]
-- >>> crossProduct [2,3,4] [5,6,7]
-- [-3.0,6.0,-3.0]
crossProduct :: [Double] -> [Double] -> [Double]
crossProduct = undefined

-- | Classify a vector by its properties using guards.
--   "zero"       if all components are 0
--   "unit"       if norm == 1 (within epsilon 1e-9)
--   "sparse"     if more than half the components are 0
--   "dense"      otherwise
-- >>> classifyVector [0,0,0]
-- "zero"
-- >>> classifyVector [1,0,0]
-- "unit"
-- >>> classifyVector [0,0,0,5]
-- "sparse"
-- >>> classifyVector [1,2,3]
-- "dense"
classifyVector :: [Double] -> String
classifyVector = undefined

-- | Determine the relationship between two vectors using guards.
--   "parallel"      if cross product is zero (3D only) or one is scalar multiple of other
--   "perpendicular" if dot product is 0 (within epsilon 1e-9)
--   "acute"         if dot product > 0
--   "obtuse"        if dot product < 0
-- >>> vectorRelation [1,0,0] [0,1,0]
-- "perpendicular"
-- >>> vectorRelation [1,2,3] [2,4,6]
-- "parallel"
-- >>> vectorRelation [1,1,0] [1,0,0]
-- "acute"
vectorRelation :: [Double] -> [Double] -> String
vectorRelation = undefined

-- | Project vector u onto vector v.
--   proj_v(u) = ((u · v) / (v · v)) * v
--   Use where or let bindings.
-- >>> projectOnto [3,4] [1,0]
-- [3.0,0.0]
-- >>> projectOnto [1,2,3] [0,0,1]
-- [0.0,0.0,3.0]
projectOnto :: [Double] -> [Double] -> [Double]
projectOnto = undefined

-- | Extract a specific element from a matrix using case expression.
--   Rows and columns are 0-indexed.
--   Return Nothing for out-of-bounds access.
-- >>> matrixGet [[1,2],[3,4]] 0 1
-- Just 2.0
-- >>> matrixGet [[1,2],[3,4]] 2 0
-- Nothing
matrixGet :: [[Double]] -> Int -> Int -> Maybe Double
matrixGet = undefined


-- =============================================================================
-- PART 4: MATRIX OPERATIONS WITH RECURSION (Ch05 — Recursion)
-- =============================================================================

-- | Transpose a matrix (swap rows and columns). Implement recursively.
-- >>> transposeM [[1,2,3],[4,5,6]]
-- [[1.0,4.0],[2.0,5.0],[3.0,6.0]]
transposeM :: [[Double]] -> [[Double]]
transposeM = undefined

-- | Multiply two matrices. Use recursion over the rows of the first matrix.
--   A (m×n) * B (n×p) = C (m×p)
--   C_ij = sum of A_ik * B_kj for k = 1..n
-- >>> matMul [[1,2],[3,4]] [[5,6],[7,8]]
-- [[19.0,22.0],[43.0,50.0]]
-- >>> matMul [[1,0],[0,1]] [[5,6],[7,8]]
-- [[5.0,6.0],[7.0,8.0]]
matMul :: [[Double]] -> [[Double]] -> [[Double]]
matMul = undefined

-- | Compute the determinant of a square matrix. Use recursive expansion
--   along the first row (cofactor expansion).
-- >>> determinant [[3]]
-- 3.0
-- >>> determinant [[1,2],[3,4]]
-- -2.0
-- >>> determinant [[1,2,3],[4,5,6],[7,8,9]]
-- 0.0
-- >>> determinant [[2,1,3],[0,4,1],[5,2,6]]
-- 29.0
determinant :: [[Double]] -> Double
determinant = undefined

-- | Compute the minor matrix: delete row i and column j (0-indexed).
-- >>> minor [[1,2,3],[4,5,6],[7,8,9]] 0 0
-- [[5.0,6.0],[8.0,9.0]]
-- >>> minor [[1,2,3],[4,5,6],[7,8,9]] 1 1
-- [[1.0,3.0],[7.0,9.0]]
minor :: [[Double]] -> Int -> Int -> [[Double]]
minor = undefined

-- | Compute the trace of a square matrix (sum of diagonal elements).
--   Implement recursively.
-- >>> trace' [[1,2],[3,4]]
-- 5.0
-- >>> trace' [[1,0,0],[0,2,0],[0,0,3]]
-- 6.0
trace' :: [[Double]] -> Double
trace' = undefined

-- | Generate an n×n identity matrix recursively.
-- >>> identityM 3
-- [[1.0,0.0,0.0],[0.0,1.0,0.0],[0.0,0.0,1.0]]
identityM :: Int -> [[Double]]
identityM = undefined

-- | Apply Gaussian elimination forward pass to a matrix (row echelon form).
--   Recursively process each pivot position.
--   (Bonus/challenge — skip if too hard for now)
-- >>> rowEchelon [[2,1,1],[4,3,3],[8,7,9]]
-- [[2.0,1.0,1.0],[0.0,1.0,1.0],[0.0,0.0,2.0]]
rowEchelon :: [[Double]] -> [[Double]]
rowEchelon = undefined


-- =============================================================================
-- PART 5: HIGHER-ORDER FUNCTIONS (Ch06 — map, filter, folds, $, composition)
-- =============================================================================

-- | Scale every vector in a list by a given scalar using map.
-- >>> scaleAll 2 [[1,2],[3,4],[5,6]]
-- [[2.0,4.0],[6.0,8.0],[10.0,12.0]]
scaleAll :: Double -> [[Double]] -> [[Double]]
scaleAll = undefined

-- | Sum a list of vectors element-wise using foldl1.
-- >>> vectorSum [[1,2,3],[4,5,6],[7,8,9]]
-- [12.0,15.0,18.0]
vectorSum :: [[Double]] -> [Double]
vectorSum = undefined

-- | Compute a linear combination: c1*v1 + c2*v2 + ... + cn*vn.
--   Use zipWith and foldl1.
-- >>> linearCombination [2,3] [[1,0],[0,1]]
-- [2.0,3.0]
-- >>> linearCombination [1,1,1] [[1,0,0],[0,1,0],[0,0,1]]
-- [1.0,1.0,1.0]
linearCombination :: [Double] -> [[Double]] -> [Double]
linearCombination = undefined

-- | Matrix-vector multiplication using map and dot products.
--   A * v = [row_i · v for each row_i in A]
-- >>> matVecMul [[1,2],[3,4]] [5,6]
-- [17.0,39.0]
matVecMul :: [[Double]] -> [Double] -> [Double]
matVecMul = undefined

-- | Transpose a matrix using map and higher-order functions (no explicit recursion).
-- >>> transposeMHOF [[1,2,3],[4,5,6]]
-- [[1.0,4.0],[2.0,5.0],[3.0,6.0]]
transposeMHOF :: [[Double]] -> [[Double]]
transposeMHOF = undefined

-- | Filter vectors from a list that are longer than a given threshold.
-- >>> filterByNorm 5 [[3,4],[1,1],[5,12]]
-- [[5.0,12.0]]
filterByNorm :: Double -> [[Double]] -> [[Double]]
filterByNorm = undefined

-- | Apply a transformation matrix to every vector in a list using map.
-- >>> transformAll [[0,-1],[1,0]] [[1,0],[0,1],[1,1]]
-- [[0.0,1.0],[-1.0,0.0],[-1.0,1.0]]
transformAll :: [[Double]] -> [[Double]] -> [[Double]]
transformAll = undefined

-- | Compute the Gram matrix: G_ij = dot(v_i, v_j).
--   Use map and function composition.
-- >>> gramMatrix [[1,0],[0,1]]
-- [[1.0,0.0],[0.0,1.0]]
-- >>> gramMatrix [[1,1],[1,-1]]
-- [[2.0,0.0],[0.0,2.0]]
gramMatrix :: [[Double]] -> [[Double]]
gramMatrix = undefined

-- | Check if a set of vectors is orthogonal (all pairwise dot products = 0).
--   Use filter, map, and function composition.
-- >>> isOrthogonalSet [[1,0,0],[0,1,0],[0,0,1]]
-- True
-- >>> isOrthogonalSet [[1,1],[1,-1]]
-- True
-- >>> isOrthogonalSet [[1,1],[1,0]]
-- False
isOrthogonalSet :: [[Double]] -> Bool
isOrthogonalSet = undefined

-- | Gram-Schmidt orthogonalization.
--   Use foldl to process each vector, projecting out previously computed
--   orthogonal directions.
-- >>> gramSchmidt [[1,1],[1,0]]
-- [[1.0,1.0],[-0.5,0.5]]  (not normalized — raw orthogonal output is fine)
gramSchmidt :: [[Double]] -> [[Double]]
gramSchmidt = undefined

-- | Compose two linear transformations (matrix multiply using only HOFs).
--   No explicit recursion. Use map, zipWith, foldl/foldr, and (.).
-- >>> composeTransforms [[0,-1],[1,0]] [[0,-1],[1,0]]
-- [[-1.0,0.0],[0.0,-1.0]]
composeTransforms :: [[Double]] -> [[Double]] -> [[Double]]
composeTransforms = undefined

-- | Find the eigenvalue of a 2x2 matrix for a given eigenvector.
--   If Av = λv, return Just λ. If v is not an eigenvector, return Nothing.
--   Use ($) and function composition.
-- >>> eigenvalue [[2,0],[0,3]] [1,0]
-- Just 2.0
-- >>> eigenvalue [[2,0],[0,3]] [0,1]
-- Just 3.0
-- >>> eigenvalue [[2,0],[0,3]] [1,1]
-- Nothing
eigenvalue :: [[Double]] -> [Double] -> Maybe Double
eigenvalue = undefined

-- | Apply a function to every element of a matrix using map composed with map.
-- >>> matrixMap (*2) [[1,2],[3,4]]
-- [[2.0,4.0],[6.0,8.0]]
-- >>> matrixMap negate [[1,-2],[3,-4]]
-- [[-1.0,2.0],[-3.0,4.0]]
matrixMap :: (Double -> Double) -> [[Double]] -> [[Double]]
matrixMap = undefined

-- | Compute the Frobenius norm of a matrix: sqrt(sum of squares of all elements).
--   Use folds, map, and (.).
-- >>> frobeniusNorm [[1,2],[3,4]]
-- 5.477225575051661
frobeniusNorm :: [[Double]] -> Double
frobeniusNorm = undefined

-- | Power of a matrix: compute A^n using foldl and matrix multiplication.
-- >>> matPow [[1,1],[0,1]] 3
-- [[1.0,3.0],[0.0,1.0]]
-- >>> matPow [[0,-1],[1,0]] 4
-- [[1.0,0.0],[0.0,1.0]]
matPow :: [[Double]] -> Int -> [[Double]]
matPow = undefined
