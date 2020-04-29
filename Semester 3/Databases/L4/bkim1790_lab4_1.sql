USE master;
GO

IF EXISTS(select * from sys.databases where name='Lab4_1')
	DROP DATABASE Lab4_1

SET DATEFORMAT YMD

CREATE DATABASE Lab4_1;
GO

USE Lab4_1;
GO

DROP TABLE IF EXISTS Szerepel
DROP TABLE IF EXISTS Vetites
DROP TABLE IF EXISTS Szineszek 
DROP TABLE IF EXISTS Mufajok
DROP TABLE IF EXISTS Filmek
DROP TABLE IF EXISTS Studiok

CREATE TABLE Szineszek(
	SzineszID INT IDENTITY,
	VezetekNev VARCHAR(50),
	KeresztNev VARCHAR(50),
	SzulDatum DATE,
	EmailCim VARCHAR(50),
	CONSTRAINT PK_Szineszek PRIMARY KEY (SzineszID)
)

CREATE TABLE Mufajok(
	MufajID INT IDENTITY,
	MufajNev VARCHAR(100),
	CONSTRAINT PK_Mufajok PRIMARY KEY (MufajID),
)

CREATE TABLE Studiok(
	StudioID INT IDENTITY,
	StudioNev VARCHAR(50),
	StudioCim VARCHAR(50),
	Bevetel DECIMAL(18,2),
	CONSTRAINT PK_Studiok PRIMARY KEY (StudioID)
)

CREATE TABLE Filmek(
	FilmID INT IDENTITY,
	FilmCim VARCHAR(100),
	StudioID INT,
	MufajID INT,
	Csillag INT,
	MegjEv INT,
	Hossz INT,
	CONSTRAINT PK_Filmek PRIMARY KEY (FilmID),
	CONSTRAINT FK_Filmek_Studiok FOREIGN KEY (StudioID) REFERENCES Studiok(StudioID),
	CONSTRAINT FK_Filmek_Mufajok FOREIGN KEY (MufajID) REFERENCES Mufajok(MufajID)
)

CREATE TABLE Szerepel(
	SzineszID INT,
	FilmID INT,
	CONSTRAINT PK_Szerepel PRIMARY KEY (SzineszID,FilmID),
	CONSTRAINT FK_Szerepel_Szineszek FOREIGN KEY (SzineszID) REFERENCES Szineszek(SzineszID),
	CONSTRAINT FK_Szerepel_Filmek FOREIGN KEY (FilmID) REFERENCES Filmek(FilmID)
)

CREATE TABLE Vetites(
	FilmID INT,
	VetitesIdopontja DATETIME,
	Terem INT,
	CONSTRAINT PK_Vetites PRIMARY KEY (FilmID, VetitesIdopontja),
	CONSTRAINT FK_Vetites_Filmek FOREIGN KEY (FilmID) REFERENCES Filmek(FilmID)
)

INSERT INTO Szineszek (VezetekNev, KeresztNev, SzulDatum, EmailCim) VALUES ('Crowe', 'Russel', '1964-04-07', 'russel@gmail.com')
INSERT INTO Szineszek (VezetekNev, KeresztNev, SzulDatum, EmailCim) VALUES ('Affleck', 'Ben', '1972-08-15', 'ben@testmail.com')
INSERT INTO Szineszek (VezetekNev, KeresztNev, SzulDatum, EmailCim) VALUES ('Hathaway', 'Anne', '1982-11-12', 'anne@testmail.com')
INSERT INTO Szineszek (VezetekNev, KeresztNev, SzulDatum, EmailCim) VALUES ('Diaz', 'Cameron', '1972-08-30', 'cameron@gmail.com')
INSERT INTO Szineszek (VezetekNev, KeresztNev, SzulDatum, EmailCim) VALUES ('Cruise', 'Tom', '1962-07-03', 'tom@gmail.com')
INSERT INTO Szineszek (VezetekNev, KeresztNev, SzulDatum, EmailCim) VALUES ('Barrymore', 'Drew', '1975-02-22', 'drew@gmail.com')

INSERT INTO Mufajok (MufajNev) VALUES ('sci-fi')
INSERT INTO Mufajok (MufajNev) VALUES ('drama')
INSERT INTO Mufajok (MufajNev) VALUES ('comedy')
INSERT INTO Mufajok (MufajNev) VALUES ('romantic comedy')
INSERT INTO Mufajok (MufajNev) VALUES ('crime')

INSERT INTO Studiok (StudioNev, StudioCim, Bevetel) VALUES ('Paramount Pictures', 'Hollywood, Los Angeles', 80000)
INSERT INTO Studiok (StudioNev, StudioCim, Bevetel) VALUES ('Colombia Pictures', 'Hollywood, Los Angeles', 60000)
INSERT INTO Studiok (StudioNev, StudioCim, Bevetel) VALUES ('London Film Studio', 'London', 10000)
INSERT INTO Studiok (StudioNev, StudioCim, Bevetel) VALUES ('Walt Disney Productions', 'Hollywood, Los Angeles', 770000)
INSERT INTO Studiok (StudioNev, StudioCim, Bevetel) VALUES ('Universal Pictures', 'Singapore', 880000)

INSERT INTO Filmek (FilmCim, StudioID, MufajID, Csillag, MegjEv, Hossz) VALUES ('Les Miserables', 1, 2, 5, 2012, 158)
INSERT INTO Filmek (FilmCim, StudioID, MufajID, Csillag, MegjEv, Hossz) VALUES ('Gladiator', 5, 2, 4, 2000, 155)
INSERT INTO Filmek (FilmCim, StudioID, MufajID, Csillag, MegjEv, Hossz) VALUES ('Argo', 2, 5, 3, 2012, 120)
INSERT INTO Filmek (FilmCim, StudioID, MufajID, Csillag, MegjEv, Hossz) VALUES ('Vanilla Sky', 5, 4, 1, 2001, 115)
INSERT INTO Filmek (FilmCim, StudioID, MufajID, Csillag, MegjEv, Hossz) VALUES ('Gone girl', 5, 1, 3, 2014, 115)

INSERT INTO Szerepel (SzineszID, FilmID) VALUES (1, 1)
INSERT INTO Szerepel (SzineszID, FilmID) VALUES (1, 2)
INSERT INTO Szerepel (SzineszID, FilmID) VALUES (2, 3)
INSERT INTO Szerepel (SzineszID, FilmID) VALUES (4, 4)
INSERT INTO Szerepel (SzineszID, FilmID) VALUES (5, 4)
INSERT INTO Szerepel (SzineszID, FilmID) VALUES (2, 5)

INSERT INTO Vetites (FilmID, VetitesIdopontja, Terem) VALUES (1, '2012-12-12 18:00:00', 3)
INSERT INTO Vetites (FilmID, VetitesIdopontja, Terem) VALUES (1, '2018-12-12 18:00:00', 6)
INSERT INTO Vetites (FilmID, VetitesIdopontja, Terem) VALUES (1, '2019-12-12 18:00:00', 7)
INSERT INTO Vetites (FilmID, VetitesIdopontja, Terem) VALUES (1, '2019-11-12 16:30:00', 3)
INSERT INTO Vetites (FilmID, VetitesIdopontja, Terem) VALUES (2, '2019-11-12 18:00:00', 1)
INSERT INTO Vetites (FilmID, VetitesIdopontja, Terem) VALUES (4, '2019-11-12 22:15:00', 4)


-------------------------------------------HAZI-------------------------------------------------



--SELECT * FROM Szineszek
--SELECT * FROM Szerepel


--Adjuk meg a ‘gmail’ email címmel rendelkező színészek  esetén, hogy hány filmben szerepeltek az elmúlt egy évben! 
--(Szineszek.VezetekNev, Szineszek.KeresztNev, Szineszek.EmailCim, FilmekSzama)

SELECT Szineszek.VezetekNev,Szineszek.KeresztNev,Szineszek.EmailCim,COUNT(*) as FilmekSzama FROM Szineszek
JOIN Szerepel ON Szineszek.SzineszID=Szerepel.SzineszID
WHERE Szineszek.EmailCim like '%gmail%'
GROUP BY Szineszek.VezetekNev,Szineszek.KeresztNev,Szineszek.EmailCim;

--Adjuk meg a legnépszerűbb (leggyakrabban vetített) filmeket! (Filmek.FilmCim)
--SELECT * FROM Filmek
--SELECT * FROM Vetites
SELECT Filmek.FilmCim,Count(Filmek.FilmID) as Hanyszor
FROM Filmek
JOIN Vetites ON Filmek.FilmID=Vetites.FilmID
GROUP BY Filmek.FilmID,Filmek.FilmCim;

--Adjuk meg stúdiónként az ott gyártott filmek számát! 
--Azokat a stúdiókat is jelenítsük meg, ahol egyetlen filmet sem gyártottak! (Studiok.StudioNev, FilmekSzama)


--SELECT * FROM Studiok
--SELECT * FROM Filmek

SELECT Studiok.StudioNev,COUNT(Filmek.StudioID) as FilmekSzama
FROM Studiok
LEFT JOIN Filmek ON Filmek.StudioID=Studiok.StudioID
GROUP BY Studiok.StudioID,Studiok.StudioNev

--Adjuk meg a legfiatalabb színész(ek) 
--melyik film(ek)ben szerepeltek! 
--(Szineszek.VezetekNev, Szineszek.KeresztNev, Filmek.FilmCim)
--SELECT * FROM Szineszek 
--Select * FROM Filmek
--SELECT * FROM Szerepel

SELECT Szineszek.VezetekNev,Szineszek.KeresztNev,Filmek.FilmCim
FROM Szineszek
JOIN Szerepel ON Szineszek.SzineszID=Szerepel.SzineszID
JOIN Filmek ON Filmek.FilmID=Szerepel.FilmID	
JOIN (
	SELECT TOP 1 Szineszek.SzulDatum, MAX(Szineszek.SzulDatum) as LegFiatalabb
	FROM Szineszek
	JOIN Szerepel ON Szineszek.SzineszID=Szerepel.SzineszID
	JOIN Filmek ON Filmek.FilmID=Szerepel.FilmID	
	GROUP BY Szineszek.SzulDatum
	ORDER BY Szineszek.SzulDatum DESC
	)LF ON Szineszek.SzulDatum=LF.LegFiatalabb
GROUP BY Szineszek.SzulDatum,Szineszek.VezetekNev,Szineszek.KeresztNev,Filmek.FilmCim
ORDER BY Szineszek.SzulDatum DESC

--Adjuk meg minden színész esetén azoknak a filmeknek az átlaghosszát, amelyekben az adott színész szerepelt. 
--Csak olyan színészeket jelenítsünk meg, akik szerepeltek legalább 2 filmben! (Szineszek.VezetekNev, Szineszek.KeresztNev, AtlagFilmHossz)

--SELECT * FROM Szineszek
--SELECT * FROM Szerepel
--SELECT * FROM Filmek 

SELECT Szineszek.VezetekNev,Szineszek.KeresztNev,AVG(Filmek.Hossz) as Atlag
FROM Szineszek
JOIN Szerepel ON Szineszek.SzineszID=Szerepel.SzineszID
JOIN Filmek ON Szerepel.FilmID=Filmek.FilmID
JOIN (
	SELECT Szineszek.VezetekNev,Szineszek.KeresztNev, COUNT(Szineszek.VezetekNev) as FilmekSzama
	FROM Szineszek
	JOIN Szerepel ON Szineszek.SzineszID=Szerepel.SzineszID
	JOIN Filmek ON Szerepel.FilmID=Filmek.FilmID
	GROUP BY Szineszek.VezetekNev, Szineszek.KeresztNev
	) HF ON Szineszek.VezetekNev=HF.VezetekNev

WHERE FilmekSzama >=2
GROUP BY Szineszek.VezetekNev,Szineszek.KeresztNev
	

--Adjuk meg azon színészeket, akik 30 évnél idősebbek és NEM szerepeltek egyetlen filmben sem,
--a vezetéknevük szerint ABC sorrendben! (Szineszek.VezetekNev, Szineszek.KeresztNev)

--SELECT * FROM Szineszek
--SELECT * FROM Szerepel
SELECT Szineszek.VezetekNev,Szineszek.KeresztNev
FROM Szineszek
WHERE YEAR(getdate()) - YEAR(Szineszek.SzulDatum) >=30
INTERSECT
SELECT Szineszek.VezetekNev,Szineszek.KeresztNev
FROM Szineszek
LEFT JOIN Szerepel ON Szerepel.SzineszID=Szineszek.SzineszID
WHERE Szerepel.SzineszID is NULL
ORDER BY Szineszek.VezetekNev ASC

--Adjuk meg azon filmeket, melyeknek a Csillag értéke maximális, 
--a ‘drama’ műfajhoz tartoznak, és legalább háromszor vetítették őket! 
--Rendezzük csökkenő sorrendbe ezeket a filmeket a vetítéseik száma alapján! 
--(Filmek.FilmCim, VetitesekSzama)


--SELECT * FROM Filmek
--SELECT * FROM Vetites

SELECT Filmek.FilmCim,COUNT(*) AS VetitesekSzama
FROM Filmek
JOIN (SELECT Filmek.FilmCim
FROM Filmek
WHERE Filmek.Csillag=(SELECT Max(Csillag) FROM Filmek)) Cs ON Cs.FilmCim=Filmek.FilmCim

JOIN (SELECT Filmek.FilmCim
FROM Filmek
JOIN Mufajok ON Filmek.MufajID=Mufajok.MufajID
WHERE Mufajok.MufajNev like '%drama%') MF ON MF.FilmCim=Filmek.FilmCim

JOIN Vetites ON Filmek.FilmID=Vetites.FilmID
GROUP BY Filmek.FilmCim
HAVING Count(*)>=3
ORDER BY Filmek.FilmCim DESC

--Adjuk meg azon színész(eke)t, aki(k) CSAK az ‘Argo’ című filmben szerepeltek!  HIBAS
--(Szineszek.VezetekNev, Szineszek.KeresztNev)
--SELECT * FROM Szineszek
--SELECT * FROM Szerepel
--SELECT * FROM Filmek

SELECT Szineszek.VezetekNev,Szineszek.KeresztNev
FROM Szineszek
JOIN Szerepel ON Szineszek.SzineszID=Szerepel.SzineszID
JOIN Filmek ON Szerepel.FilmID=Filmek.FilmID
GROUP BY Szineszek.VezetekNev,Szineszek.KeresztNev
HAVING Count(Szineszek.VezetekNev)=1
INTERSECT
SELECT Szineszek.VezetekNev,Szineszek.KeresztNev
FROM Szineszek
JOIN Szerepel ON Szineszek.SzineszID=Szerepel.SzineszID
JOIN Filmek ON Szerepel.FilmID=Filmek.FilmID
WHERE Filmek.FilmCim like '%Argo%'
GROUP BY Szineszek.VezetekNev,Szineszek.KeresztNev

--Adjuk meg azon színészeket, akik játszottak ‘sci-fi’ 
--ÉS ‘crime’ műfajú filmekben is! (Szineszek.VezetekNev, Szineszek.KeresztNev)


SELECT Szineszek.VezetekNev,Szineszek.KeresztNev
FROM Szineszek
JOIN Szerepel ON Szineszek.SzineszID=Szerepel.SzineszID
JOIN Filmek ON Szerepel.FilmID=Filmek.FilmID
JOIN Mufajok ON Mufajok.MufajID=Filmek.MufajID
WHERE MufajNev like '%sci-fi%'
GROUP BY Szineszek.VezetekNev,Szineszek.KeresztNev
INTERSECT
SELECT Szineszek.VezetekNev,Szineszek.KeresztNev
FROM Szineszek
JOIN Szerepel ON Szineszek.SzineszID=Szerepel.SzineszID
JOIN Filmek ON Szerepel.FilmID=Filmek.FilmID
JOIN Mufajok ON Mufajok.MufajID=Filmek.MufajID
WHERE MufajNev like '%crime%'
GROUP BY Szineszek.VezetekNev,Szineszek.KeresztNev

--Adjuk meg azon filmeket, melyekben játszott ‘Russel Crowe’, DE NEM játszott ‘Anne Hathaway’! (Filmek.FilmCim)

--SELECT * FROM Szineszek
--SELECT * FROM Szerepel
--SELECT * FROM Filmek

SELECT Filmek.FilmCim
FROM Filmek
JOIN Szerepel ON Szerepel.FilmID=Filmek.FilmID
JOIN Szineszek ON Szerepel.SzineszID=Szineszek.SzineszID
WHERE Szineszek.VezetekNev like '%Crowe%' and Szineszek.KeresztNev like '%Russel%'
EXCEPT
SELECT Filmek.FilmCim
FROM Filmek
JOIN Szerepel ON Szerepel.FilmID=Filmek.FilmID
JOIN Szineszek ON Szerepel.SzineszID=Szineszek.SzineszID
WHERE Szineszek.VezetekNev like '%Hathaway' and Szineszek.KeresztNev like '%Anne%'
