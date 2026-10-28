-- limits.hs

steps :: [Double]
steps = take 8 (iterate (/ 10) 0.1)

approachRight :: (Double -> Double) -> Double -> [Double]
approachRight f a = [f (a + h) | h <- take 5 steps]

approachLeft :: (Double -> Double) -> Double -> [Double]
approachLeft f a = [f (a - h) | h <- take 5 steps]

limitAt :: (Double -> Double) -> Double -> Maybe Double
limitAt f a
  | abs (l - r) < 1e-4 = Just ((l + r) / 2)
  | otherwise = Nothing
  where
    h = 1e-6
    l = f (a - h)
    r = f (a + h)

-- lim g(f(x))
-- x->-2
--
-- lim f(x) = 3 (from below, from both sides)
-- x->-2
--
-- u = f(x)
-- lim g(u) = 1
-- u->3-
g :: Double -> Double
g u = if u < 3 then 1 else -1

f1, f2 :: Double -> Double
f1 x = 3 - abs (x + 2)
f2 x = 3 + (x + 2)

-- we can check the `limitAt` by passing the following expression:
-- `limitAt (g . f1) -2` and we should expect Just 1.0
-- `limitAt (g . f2) -2` and we should expect Nothing


