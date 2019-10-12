{- stack
  runghc
  --package data-ordlist
-}

module Main where
import           Prelude
import           System.IO
import           Data.List.Ordered
import           Data.Ord
-- data-ordlist

main :: IO ()

main = do
  -- handle   <- openFile "nums.txt" WriteMod
  -- contents <- hGetContents handle
  -- hClose handle
  -- writeFile "num.txt"
  --   $ foldl (\a b -> a ++ b ++ "\n") "" (map show (take 10000 uglyNums))
  print (uglyNums !! 1498)
  print (uglyNums !! 1499)
  print (uglyNums !! 1500)
  print (uglyNums !! 1501)
  return ()


ugly :: (Integer, Integer, Integer) -> Integer
ugly (x, y, z) = 2 ^ x * 3 ^ y * 5 ^ z
norm = ugly -- UGLY IS THE NORM!
-- norm (x,y,z) = sqrt (fromIntegral x ^ 2 + fromIntegral y ^ 2 + fromIntegral z ^ 2)
mergeByNorm = mergeAllBy (comparing norm)
sorted = mergeByNorm
  (map mergeByNorm
       [ [ [ (x, y, z) | x <- [0 ..] ] | y <- [0 ..] ] | z <- [0 ..] ]
  )

uglyNums :: [Integer]
uglyNums = [ ugly t | t <- sorted ]

answer = uglyNums !! 1500

-- 860934420 sounds reasonable
