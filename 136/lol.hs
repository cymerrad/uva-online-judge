module Main where

import           Data.List.Ordered
import           Data.Ord
-- data-ordlist
norm (x, y, z) =
  sqrt (fromIntegral x ^ 2 + fromIntegral y ^ 2 + fromIntegral z ^ 2)
mergeByNorm = mergeAllBy (comparing norm)
sorted = mergeByNorm
  (map mergeByNorm
       [ [ [ (x, y, z) | x <- [0 ..] ] | y <- [0 ..] ] | z <- [0 ..] ]
  )
ugly (x, y, z) = 2 ^ x * 3 ^ y * 5 ^ z
uglyNums = [ ugly t | t <- sorted ]

aLotOf = 100000 -- 10000 gives a different result!
(sort (take aLotOf uglyNums)) !! 1500

-- 860934420 sounds reasonable
