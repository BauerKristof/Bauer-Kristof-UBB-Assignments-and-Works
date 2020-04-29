--Kérdezzük le a Stílusok tábla tartalmát!
SELECT * FROM Stilusok;

--Adjuk meg az első 5 művészt az adatbázisból, vezetéknevüket és keresztnevüket nagybetűkkel írva (MVezetekNev, MKeresztNev, SzOrszag, SzulDatum)!
SELECT TOP 5 MVezetekNev,MKeresztNev,SzOrszag,SzulDatum FROM Muveszek;

--Adjuk meg azon művészeket, vezetéknév szerint ABC sorrendben, akik vezetéknevének második betűje ‘S’ (MVezetekNev, MKeresztNev)!
SELECT MVezetekNev,MKeresztNev FROM  Muveszek WHERE SUBSTRING(MVezetekNev,2,1) =  'S' ORDER BY MVezetekNev ASC;

--Adjuk meg azokat a művészeket, akik 'Románia'-ból származnak, és az év első 6 hónapjában születtek (MVezetekNev, MKeresztNev, SzulDatum, EmailCim)! 
SELECT MVezetekNev,MKeresztNev,SzulDatum,EmailCim FROM Muveszek WHERE SzOrszag='RO'AND MONTH(SzulDatum)>=1 AND MONTH(SzulDatum) <=6

--Adjuk meg azon jegytípusokat, melyeknek az ára 50 és 100 között van (JTNev)!
SELECT JTNev FROM JegyTipusok WHERE Ar>=50 AND Ar<=100

--Adjuk meg azon színpadokat, melyeken fellépnek olyan zenészek, melyek a következő listában szereplő stílusok valamelyikében játszanak: (‘techno’, ‘house’, ‘pop’) (SzNev, Cim)! Minden színpad csak egyszer jelenjen meg az eredményben!
SELECT SZ.SZNev, SZ.Cim FROM MUVESZEK M
JOIN SZINPADOK SZ ON SZ.SzID=M.SzinpadID
JOIN Stilusok st ON M.StilusID=ST.StilusID
WHERE st.SNev like '%house%' or st.SNev like '%pop%' or st.SNev like '%techno%' 

--Adjuk meg azon jegytípusokat, melyekből vásároltak ‘David Guetta’ koncertjére, ár szerint csökkenő sorrendben (JTNev)!
SELECT JT.JTNev,JT.Ar FROM Muveszek M
JOIN RESZVETEL R ON R.MID=M.MID
JOIN JEGYEK J ON J.JegyKod=R.Jegykod
JOIN JEGYTIPUSOK JT ON J.JTID=JT.JTID
WHERE M.MVezetekNev='David' AND M.MKeresztNev='Guetta'
ORDER BY JT.Ar DESC

--Adjuk meg azon művészek honoráriumának átlagát, akik a ‘Szinpad1’ nevű színpadon léptek fel (AtlagHonorarium)!
SELECT AVG(Honorarium) FROM Muveszek M
JOIN Szinpadok SZ ON SZ.SzID=M.SzinpadID
WHERE SZ.SZNev='Szinpad1'

--Adjuk meg a legdrágább jegytípus árát (LegdragabbAr)! 
SELECT MAX(Ar) FROM JegyTipusok

--Adjuk meg azon művészek nevét, alakulási évét, akiknek két hónappal ezelőtt volt a születésnapjuk és felléptek valamelyik nap ‘23’ óra után (MVezetekNev, MKeresztNev, AlakulasiEv)!
SELECT MVezetekNev, MKeresztNev, AlakulasiEv FROM Muveszek
WHERE MONTH(GETDATE())-2=MONTH(SzulDatum) AND KezdIdopont>=23

--Módosítsuk  ‘David Guetta’ koncertjének időpontját  ‘3’.nap  ‘22.00’ órára, honoráriumát pedig növeljük meg 10%-kal!  

--SELECT * FROM Muveszek
UPDATE Muveszek
SET KoncertNap = 3,
KezdIdopont=22,
 Honorarium=Honorarium+(Honorarium*10)/100
WHERE Muveszek.MVezetekNev='David' AND Muveszek.MKeresztNev='Guetta';
--SELECT * FROM Muveszek

--Töröljük azokat a művészeket, akik az Untold  ‘1.’ napján felléptek! 
--Más koncertnap megadása esetén a művészek között legyen min 1 olyan, akinek a koncertjére adtak már el legalább 1 jegyet!

DELETE R FROM Reszvetel as R
	inner join Muveszek on R.MID = Muveszek.MID WHERE KoncertNap = 1;
DELETE FROM Muveszek WHERE KoncertNap = 1

