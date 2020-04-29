duplaz::[a]->[a]
duplaz [] = []
duplaz (x:xs) =x:x:duplaz xs --meghivod x,x-re osszefuzve duplaz:xs fuggvenyhivas a tailre

f :: Integer -> Integer
f 0 = 0
f 1 = 1
f n = f (n-1) + f (n-2)


fib :: Num t => t -> t -> [t]
fib a b = a : fib b (a + b)
--take 30 $ fib 0 1
--take 150 $ fib 0 1

minElem::[Int]->Int
minElem [] = 0
minElem [x] = x
minElem (x:y:xs) 
 |x > y = minElem (y:xs)
 |x < y = minElem (x:xs)
 |x == y = minElem (x:xs)


maxok::[Integer]->[Integer]
maxok [] = []
maxok [x,y]=[x,y]
maxok (x:y:z:xs)
 |x>y && y>z = maxok(x:y:xs)
 |x>y && z>y = maxok(x:z:xs)
 |y>x && z>x = maxok(y:z:xs)
 |x==y = maxok(x:z:xs)
 |y==z = maxok(x:y:xs)
 |x==z = maxok(x:y:xs)
 |otherwise = maxok(x:y:xs)

oszt::[a] -> ([a], [a])
oszt [] = ([],[])
oszt [x] = ([x],[])
oszt (x:y:xys) = (x:xs,y:ys) where (xs,ys) =oszt xys

merge :: (Ord a) => [a] -> [a] -> [a]
merge x [] = x
merge [] y = y
merge (x:xs) (y:ys)
  | x < y     = x:(merge xs (y:ys))
  | otherwise = y:(merge (x:xs) ys)


lnko :: (Integral a) => a->a->a
lnko x y
    | x == y = x
    | x>y = lnko(x-y) y
    | otherwise = lnko x (y-x)

lkkt :: (Integral a) => a->a->a
lkkt x y = (x*y) `div`(lnko x y)

pali :: (Eq a) => [a] -> Bool
pali x = x == (reverse x)

torolk::[Integer]->Integer->Integer->[Integer]
torolk [] _ _ = []
torolk (x:xs) k i
    |i<k = x:torolk(xs) k j
    |i==k = torolk(xs) k 1
    where
    j=i+1

torol::[Integer]->Integer->[Integer]
torol [] _ = []
torol (x:xs) k = torolk(x:xs) k 1


kompakt :: (Eq a,Num b) => [a] -> [(a, b)]
kompakt (x:xs) = eloFordulas 1 x xs where
  eloFordulas n x [] = [(x,n)]
  eloFordulas n x (y:ys)
    | x==y = eloFordulas (n+1) x ys
    | otherwise = (x,n) : eloFordulas 1 y ys
kompakt _ = []

