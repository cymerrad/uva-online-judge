{- stack
  runghc
  --package data-ordlist
-}

module Main where
import           Prelude
import           System.IO
import           Data.List.Ordered
import           Data.Ord

main :: IO ()
main = do
  print answer
  return ()

-- UGLY IS THE NORM!
norm :: (Integer, Integer, Integer) -> Integer
norm (x, y, z) = 2 ^ x * 3 ^ y * 5 ^ z

mergeByNorm = mergeAllBy (comparing norm)
sorted = mergeByNorm
  (map mergeByNorm
       [ [ [ (x, y, z) | x <- [0 ..] ] | y <- [0 ..] ] | z <- [0 ..] ]
  )

uglyNums :: [Integer]
uglyNums = [ norm t | t <- sorted ]

answer = uglyNums !! 1500

-- it should be 860934420
