
quicksort [] = []
quicksort (x:xs) = lower ++ [x] ++ upper
    where
        lower = quicksort (filter (<= x) xs)
        upper = quicksort (filter (> x) xs)

