
-- Exploring Lists
numbers = [3,6..30]

-- find the first element
firstNum = head numbers
findFirst lst = head lst
-- find the last element
lastNum = last numbers
findLast lst = last lst
-- find everything except the first element
exceptFirst = tail numbers
findAllExceptFirst lst = tail lst
-- find everything except the last element
exceptLast = init numbers
findAllExceptLast lst = init lst
-- find the length
numbersLength = length numbers
findLength lst = length lst
-- reverse the list
reversedNumbers = reverse numbers
reverseList lst = reverse lst
-- take the first five elements
firstFiveElementsFromNumbers = take 5 numbers
firstFiveElements lst = take 5 lst
-- drop the first four elements
withoutLastFourElementsFromNumbers = drop 4 numbers
withoutLastFour lst = drop 4 lst
-- compute the sum
sumOfNumbers = sum numbers
sumOf lst = sum lst
-- compute their product
productOfNumbers = product numbers
productOf lst = product lst
-- find maximum and minimum
maxNum = max numbers
minNum = min numbers
-- if a given number belongs to the list
isIn x lst = x `elem` lst -- or elem x lst

-- Ranges and List Comperhensions
hundred = [0..100]
-- all even numbers from 0 to N
evenFromZeroTo x = [y | y <- [0..x], y `mod` 2 == 0]
-- every multiple of 7 less than 100
multipleOfSeven = [x | x <- [0..100], mod x 7 == 0]
-- the squares of every number from 1 to 20
squares = [x ^ 2 | x <- [0..20]]
-- the cubes of every odd numbers from 1 to 15
cubesOfOdd = [x ^ 3 | x <- [1..15], x `mod` 2 == 1]
-- every number between 1 and 100 divisible by both 3 and 5
divBy15 = [x | x <- [1..100], x `mod` 15 == 0]
-- every uppercase letter in the string
str = "Haskell Is Fun!"
upperLetters = [c | c <- str, c `elem` ['A'..'Z']]
-- zim the two lists together
nums = zip [1..5] ["one", "two", "three", "four", "five"]

