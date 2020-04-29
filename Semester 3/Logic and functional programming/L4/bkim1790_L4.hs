import Data.Char
import Data.List
import Data.Maybe



--1.Ikerprímnek nevezzük a (6*k-1 ; 6*k+1) alakú számpárt melyben mindkettő prím. Keressük meg az összes n-nél kisebb ikerprímet.
primSzam :: Int -> Bool
primSzam n = length [ k | k <- [2..n], n `mod` k == 0] == 1

ikerPrim :: Int -> [(Int,Int)]
ikerPrim n = [(x,y) | x <- [2..n], y <- [2..n], primSzam x, primSzam y && y-x==abs 2]


--2a. Írjunk egy függvényt, mely kiszűri egy szám többszörösét egy listából
kiszur::Integral a=>[a]->a->[a]
kiszur [] _ =[]
kiszur (x:xs) elem
     |mod x elem == 0 && x /= elem = kiszur xs elem
     |otherwise = x:kiszur xs elem

--2b.Írjuk meg a szitát, alkalmazva a kiszur függvényt.
szita ::Integral a=>[a] -> [a]
szita [] = []
szita (x:xs) = x : szita (kiszur xs x)

--2c.Implementáljunk egy függvényt, mely a prímszámok közül kiválasztja az N-ediket
primSzamLista::[Integer]
primSzamLista=[2..]
valaszt::Integer->Integer
valaszt n
     |n<=0 = -9999
     |otherwise = segedValaszt primSzamLista n 1

segedValaszt::[Integer]->Integer->Integer->Integer
segedValaszt (x:xs) n i
     |i==n = x
     |otherwise = segedValaszt kiszurtLista n (i+1)
      where kiszurtLista = kiszur xs x



--3.Modellezzük a régi - nyomógombos - mobilt, ahol egy üzenetet úgy írtunk, hogy minden betűhöz egyszer vagy többször nyomtunk meg adott gombot. Az alábbiakban a gombokat adjuk meg, asszociálva a gomb kimenetével ha egyszer, kétszer ... van megnyomva (nevezzük oldPhone kódolásnak):

data OldPhone = OldPhone [(Char, String)]
type Digit = Char
type Presses = Int

phone :: OldPhone
phone = OldPhone billentzuzetLeosztas

billentzuzetLeosztas :: [(Char,String)]
billentzuzetLeosztas =

                [
                    ('0',"+ 0"),
                    ('1',"1"),
                    ('2',"aábc2"),
                    ('3',"deéf3"),
                    ('4',"ghií4"),
                    ('5',"jkl5"),
                    ('6',"mnoóöő6"),
                    ('7',"pqrs7"),
                    ('8',"tuúüűv8"),
                    ('9',"wxyz9"),
                    ('#',".,#")
                ]


--a. Adjuk meg a függvényt, mely egy mondatra - Sztring-re - megmondja, ogy ábrázolható-e az oldPhone kódolásban. Például a "Lehel! 2+4=6" nem ábrázolható.

abrazolhatoKarakterek :: Char -> Bool
abrazolhatoKarakterek x
     | x `elem` ['0'..'9'] = True
     | x `elem` ['+',' ','a','á','b','c','d','e','é','f','g','h','i','í','j','k','l','m','n','o','ó','ö','ő','p','q','r','s','t','u','ú','ü','ű','v','w','x','y','z','.',',','#'] = True
     | otherwise           = False

abrazolhato :: [Char] -> Bool
abrazolhato = all abrazolhatoKarakterek

--b. Határozzuk meg egy mondat oldPhone kódját.
oldPhoneCode::String->[(Digit, Presses)]
oldPhoneCode uzenet =krealUzenet phone uzenet

krealUzenet :: OldPhone -> String -> [(Digit, Presses)]
krealUzenet phone = foldMap (reverseTaps phone)

reverseTaps :: OldPhone -> Char -> [(Digit, Presses)]
reverseTaps phone c =
     if isUpper c
     then [('*', 1), keresKarakter phone (toLower c)]
     else [keresKarakter phone c]

keresKarakter :: OldPhone -> Char -> (Digit, Presses)
keresKarakter (OldPhone ((digit, press):tl)) c =
     case elemIndex c press of
       Just idx -> (digit, idx + 1)
       Nothing -> keresKarakter (OldPhone tl) c



--4.A cumul_op függvény implementálása:
--Írjunk függvényt, mely egy listából és egy operátorból azt a listát állítja elő, mely egy pozíciójának a k-adik eleme a bemenő lista első k elemének az op szerinti összetevése.


cumul_op :: (t -> t -> t) -> [t] -> [t]
cumul_op (op) (x:[]) = x:[]
cumul_op (op) (x:y:xs) = x : cumul_op op ((op x y):xs)


--5.Az until függvény használatával határozzuk meg egy pozitív szám természetes alapú logaritmusának - ln(y)-nek - az értékét. 
--Használjuk a következő sorbafejtést:
--ln(1+x) = - sum_{k,1,inf} (-x)^k/k
--Írjuk úgy a kódot, hogy minél hatékonyabb legyen a függvény. Alakítsuk át a divergens sorozatokat a ln(y)=-ln(1/y)összefüggéssel (amely akkor kell, ha |x|>=1).
ln y
    | y - 1 >= 1 =  - ln (1 / y)
    |otherwise  = negate $ harmadik 
    $until (\(x,k,s) -> ((-x)**k)/k < 10**(-25)  ) 
    (\(x,k,s)->(x,k+1,s+((-x)**k)/k)) 
    (y-1,1,0) 

harmadik (x,y,z)=z;
--6. Írjunk függvényt, mely egy listából CSAK az egyedi elemeket őrzi meg. Például egyedi [2,3,4,5,1,2,3,4] eredménye az [5,1] lista.

egyedi :: Eq a => [a] -> [a]
egyedi [] = []
egyedi (x:xs)
 |szerepel x xs == True = egyedi(kivesz x xs)
 |otherwise = x : egyedi xs

szerepel :: Eq t => t -> [t] -> Bool
szerepel _ [] = False
szerepel e (x:xs)
 |e == x =True
 |otherwise = szerepel e xs

kivesz :: Eq a => a -> [a] -> [a]
kivesz _ [] = []
kivesz dupla (x:xs)
 |x == dupla = kivesz dupla xs
 |otherwise = x : kivesz dupla xs

--7.Az until függvény használatával számítsuk ki a Haskell valós precizitását a kettes számrendszerben.
--A precizitás a kettőnek az a legnagyobb negatív hatványa, mely kettővel osztva nullát eredményez.
valosPrecizitas::(Integer)
valosPrecizitas =snd $ (until (\ (a,_) -> (a/2) == 0   ) 
          (\(a,k)-> (a/2,(k+1)) ) 
          (1,0))

--A bináris fák ábrázolásához tekintsük a következő típust:
--data BinFa a =
--  Nodus (BinFa a) a (BinFa a)
--   | Level
--mely egy bináris fát ábrázol. A következőkben a fákat rendezett keresési fáknak tekintjük: a nódusban található elem mindig nagyobb, mint a bal oldali fa összes eleme és kisebb a jobb oldali fa összes eleménél.
--Írjuk meg a következő függvényeket:

--8.1A beszur függvényt, mely egy bináris fába szúr be egy elemet.
data BinFa a =
   Nodus (BinFa a) a (BinFa a)
   | Level

instance Show a => Show (BinFa a)          
      where  
           show (Nodus bal a jobb) = "(" ++ show bal ++ show a ++ show jobb ++ ")"
           show Level="."
elemBeszur :: (Eq a,Ord a)=>(BinFa a)->a->(BinFa a)
elemBeszur Level x = (Nodus Level x Level)        --megallasi feltetel, beszurtuk az elmet
elemBeszur (Nodus bal k jobb) ertek 
     |ertek>k = (Nodus bal k (elemBeszur jobb ertek)) --ha a beszurando ertek nagyobb mint az aktualis csucs akkor a fa jobb oldalan halad 
     |ertek<k = (Nodus (elemBeszur bal ertek) k jobb) --ha kisebb akkor pedig bal oldalt 
     |otherwise = Nodus bal k jobb                 --ha megtalalta a megfelelo poziciot akkor beszurja

listabol :: (Ord a)=>[a]->(BinFa a) 
listabol [] = Level
listabol (f:maradek) = elemBeszur (listabol maradek) f --elemBeszur fuggvenyt hivja meg a a lista minden elemere sorban
--show(listabol[1,3,2])           

keresElem :: (Eq a,Ord a)=>(BinFa a)->a->(BinFa a)
keresElem Level _ = Level   --megallasi feltetel, ha mar csak level van akkor torli 
keresElem (Nodus bal k jobb ) ertek
     |ertek>k = (Nodus bal k (keresElem jobb ertek))        --ha a torlendo ertek nagyobb mint az aktualis csucs ->jobb oldalt
     |k>ertek = (Nodus (keresElem bal ertek) k jobb)        --ha kisebb akkor pedig bal oldalt
     |otherwise = torolElem (Nodus bal k jobb)            --ha megtalalta a helyet akkor meghivja torolElem fuggvenyt


torolElem :: (Ord a)=>(BinFa a)->(BinFa a)
torolElem (Nodus Level x jobb) = jobb                 --ha a baloldal level akkor megartja a jobb oldalt
torolElem (Nodus bal x Level) = bal                   --ha a jobboldal level akkor megartja a bal oldalt
torolElem (Nodus bal x jobb) = (Nodus bal x1 (keresElem jobb x1))--es ha az egyik sem level akkor torli es meghivja a nemlevel fuggvenyt
     where
      x1 = nemlevel jobb --rendezi a fat azzal hogy felhoz elemeket

nemlevel :: (BinFa a) -> a
nemlevel (Nodus Level x _) = x            --ha a bal oldal level akkor megallunk
nemlevel (Nodus bal _ _) = nemlevel bal   --kulonben meghivjuk onmagat a masik olalra

--9.A komplex számok a+i.b alakúak, ahol a a valós része, b az imaginárius része a számnak, az i meg a -1 négyzetgyöke. Definiáljuk a C komplex szám adattípust. Írjuk meg a show, az aritmetikai műveleteknek (+,-,*,/,abs) a Haskell kódját.

data  Komplex = Komplex(Double,Double)        --Komplex(valos,imaginarius)

instance Show Komplex     
     where 
           show (Komplex(a,b))
               |b>0 = show a ++ "+" ++ show b ++ "i"         --kiiratas a megfelelo modon
               |b<0 = show a ++ show b ++ "i"  
               |b==0 = show a

instance Num Komplex                            --aritmetikai muveletek
      where 
                Komplex(a,b) + Komplex(c,d) = Komplex(a+c,b+d) --(a+bi)+(c+di) = (a+c)+(b+d)i
                Komplex(a,b) - Komplex(c,d) = Komplex(a-c,b-d) --(a+bi)-(c+di) = (a-c)+(b-d)i
                Komplex(a,b) * Komplex(c,d) = Komplex(a*c-b*d, b*c+a*d) --(a+bi)*(c+di) = (ac-bd)+(bd+ad)
                abs(Komplex (a,b)) = Komplex (sqrt(a^2+b^2),0) --abs(a+bi) = sqrt(a^2+b^2)

instance Fractional Komplex --osztas
     where
                Komplex (a,b) / Komplex(c,d) = Komplex((a*c+b*d)/(c^2+d^2),(b*c-a*d)/(c^2+d^2))--(a+bi)/(c+di) = ((ac+bd)/(c^2+d^2))/((bc-ad)/(c^2+d^2))

