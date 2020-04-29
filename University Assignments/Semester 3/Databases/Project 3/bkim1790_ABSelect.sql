USE bkim1790_sajat4;
GO

--Egy inner join -- Adjuk meg azon soforok nevet akik 'Opel' tipusu autot vezettek

SELECT Soforok.SfNeve FROM Soforok
JOIN Vezeti ON Vezeti.SfID=Soforok.SfID
JOIN Autok ON Autok.AID=Vezeti.AID
WHERE Autok.Tipus like '%Opel%'

--Egy outer join -- Adjuk meg az osszes Internetes ceg eseten melyik szallitoceggel dolgoznak
SELECT * FROM Internetescegek
SELECT * FROM Kuldet

SELECT Internetescegek.IcNeve,SzallitoCegek.SzNev FROM Internetescegek
LEFT JOIN Kuldet ON Kuldet.IcID=Internetescegek.IcID
LEFT JOIN SzallitoCegek ON SzallitoCegek.SzID=Kuldet.SzID

--Halmazmuvelet -- Listazzuk ki azoknak a vevoknek a nevet akik csak Porszivot rendeltek  
--SELECT * FROM Vevok
--SELECT * FROM Vasarol
--SELECT * FROM Termekek

SELECT Vevok.VNeve FROM Vevok
JOIN Vasarol ON Vasarol.VID=Vevok.VID
JOIN Termekek ON Termekek.TID=Vasarol.TID
WHERE Termekek.TNeve='Porszivo'
EXCEPT
SELECT Vevok.VNeve FROM Vevok
JOIN Vasarol ON Vasarol.VID=Vevok.VID
JOIN Termekek ON Termekek.TID=Vasarol.TID
WHERE Termekek.TNeve!='Porszivo'

--Group BY+HAVING -- Adjuk meg hogy a legdragabb termek nevet es hogy hany alkalommal adtak el

SELECT Termekek.TNeve,COUNT(Termekek.TID) as HanyszorEladva
FROM Termekek
JOIN Vasarol ON Vasarol.TID=Termekek.TID
GROUP BY Termekek.TID,Termekek.TNeve,Termekek.TAr
HAVING Termekek.TAr=(SELECT MAX(Termekek.TAr) FROM Termekek)


--Osszesito fuggveny -- Adjuk meg a legkevesebb alkalommal eladott termekek nevet melyek ara maximalis

SELECT COUNT(Termekek.TID) as HanyszorEladva
INTO #TempTable
FROM Termekek
JOIN Vasarol ON Vasarol.TID=Termekek.TID
WHERE Termekek.TAr=(SELECT MAX(Termekek.TAr) FROM Termekek)
GROUP BY Termekek.TID,Termekek.TNeve,Termekek.TAr

SELECT Termekek.TNeve,COUNT(Termekek.TID) as HanyszorEladva
FROM Termekek
JOIN Vasarol ON Vasarol.TID=Termekek.TID
WHERE Termekek.TAr=(SELECT MAX(Termekek.TAr) FROM Termekek)
GROUP BY Termekek.TID,Termekek.TNeve,Termekek.TAr
HAVING COUNT(Termekek.TID)=(SELECT MIN(#TempTable.HanyszorEladva) FROM #TempTable)

DROP TABLE #TempTable
