USE master;
GO

IF EXISTS(select * from sys.databases where name='Lab5_1')
	DROP DATABASE Lab5_1

SET DATEFORMAT YMD

CREATE DATABASE Lab5_1;
GO

USE Lab5_1;
GO

DROP TABLE IF EXISTS FelhasznaloKedvencei
DROP TABLE IF EXISTS FelhasznaloPosztjai
DROP TABLE IF EXISTS Baratok
DROP TABLE IF EXISTS Felhasznalok
DROP TABLE IF EXISTS Oldalak
DROP TABLE IF EXISTS OldalTipusok

CREATE TABLE Felhasznalok(
	FelhID INT IDENTITY,
	VezetekNev VARCHAR(50),
	KeresztNev VARCHAR(50),
	Telefonszam VARCHAR(15),
	SzulDatum DATE,
	Neme VARCHAR(1),
	Email VARCHAR(50),
	CONSTRAINT PK_Felhasznalok PRIMARY KEY (FelhID)
)

CREATE TABLE Baratok(
	FelhID1 INT,
	FelhID2 INT,
	BaratsagKezdete DATETIME,
	CONSTRAINT FK_Baratok_Felhasznalok1 FOREIGN KEY (FelhID1) REFERENCES Felhasznalok(FelhID),
	CONSTRAINT FK_Baratok_Felhasznalok2 FOREIGN KEY (FelhID2) REFERENCES Felhasznalok(FelhID),
	CONSTRAINT PK_Baratok PRIMARY KEY (FelhID1, FelhID2)
)

CREATE TABLE OldalTipusok(
	OldalTipID INT IDENTITY,
	OldalTipNev VARCHAR(50),
	CONSTRAINT PK_OldalTipusok PRIMARY KEY (OldalTipID)
)

CREATE TABLE Oldalak( 
	OldalID INT IDENTITY,
	OldalMegnev VARCHAR(50),
	IndulasiEv INT, 
	Weboldal VARCHAR(50),
	OldalTipID INT,
	Csillag INT,
	CONSTRAINT PK_Oldalak PRIMARY KEY (OldalID),
	CONSTRAINT FK_Oldalak_OldalTipusok FOREIGN KEY (OldalTipID) REFERENCES OldalTipusok(OldalTipID)
)

CREATE TABLE FelhasznaloKedvencei(
	FelhID INT,
	OldalID INT,
	KiemeltE BIT,
	CONSTRAINT PK_FelhasznaloKedvencei PRIMARY KEY (FelhID,OldalID),
	CONSTRAINT FK_FelhasznaloKedvencei_Felhasznalok FOREIGN KEY (FelhID) REFERENCES Felhasznalok(FelhID),
	CONSTRAINT FK_FelhasznaloKedvencei_Oldalak FOREIGN KEY (OldalID) REFERENCES Oldalak(OLdalID)
)

CREATE TABLE FelhasznaloPosztjai(
	FelhID INT,
	OldalID INT,
	Idopont DATETIME,
	Leiras VARCHAR(max),
	CONSTRAINT PK_FelhasznaloPosztjai PRIMARY KEY (FelhId,OldalID,Idopont),
	CONSTRAINT FK_FelhasznaloPosztjai_Felhasznalok FOREIGN KEY (FelhID) REFERENCES Felhasznalok(FelhID),
	CONSTRAINT FK_FelhasznaloPosztjai_Oldalak FOREIGN KEY (OldalID) REFERENCES Oldalak(OLdalID)
)

INSERT INTO Felhasznalok (VezetekNev, KeresztNev, Telefonszam, SzulDatum, Neme, Email) VALUES ('Nagy', 'Abel', '123456789', '1989-04-10', 'M', 'abel@yahoo.com')
INSERT INTO Felhasznalok (VezetekNev, KeresztNev, Telefonszam, SzulDatum, Neme, Email) VALUES ('Kiss', 'Barna', '123456789', '1995-11-01', 'M', 'barni@gmail.com')
INSERT INTO Felhasznalok (VezetekNev, KeresztNev, Telefonszam, SzulDatum, Neme, Email) VALUES ('Szekely', 'Robert', '123456789', '1989-10-12', 'M', 'nomail@nodomain.com')
INSERT INTO Felhasznalok (VezetekNev, KeresztNev, Telefonszam, SzulDatum, Neme, Email) VALUES ('Szabo', 'Julia', '123456789', '1990-05-11', 'F', 'juli@yahoo.com')
INSERT INTO Felhasznalok (VezetekNev, KeresztNev, Telefonszam, SzulDatum, Neme, Email) VALUES ('Molnar', 'Peter', '123456789', '1991-09-01', 'M', 'peti@gmail.com')
INSERT INTO Felhasznalok (VezetekNev, KeresztNev, Telefonszam, SzulDatum, Neme, Email) VALUES ('Kovacs', 'Kata', '123456789', '1978-12-12', 'F', 'nomail@nodomain.com')
INSERT INTO Felhasznalok (VezetekNev, KeresztNev, Telefonszam, SzulDatum, Neme, Email) VALUES ('Papp', 'Maria', '123456789', '1988-05-16', 'F', 'mari@yahoo.com')
INSERT INTO Felhasznalok (VezetekNev, KeresztNev, Telefonszam, SzulDatum, Neme, Email) VALUES ('Varadi', 'Pal', '123456789', '1992-07-19', 'F', 'pali@gmail.com')

INSERT INTO Baratok (FelhID1, FelhID2, BaratsagKezdete) VALUES (3, 1, '2017-01-02')
INSERT INTO Baratok (FelhID1, FelhID2, BaratsagKezdete) VALUES (1, 3, '2017-01-02')
INSERT INTO Baratok (FelhID1, FelhID2, BaratsagKezdete) VALUES (3, 2, '2018-05-02')
INSERT INTO Baratok (FelhID1, FelhID2, BaratsagKezdete) VALUES (2, 3, '2018-05-02')
INSERT INTO Baratok (FelhID1, FelhID2, BaratsagKezdete) VALUES (3, 4, '2019-01-02')
INSERT INTO Baratok (FelhID1, FelhID2, BaratsagKezdete) VALUES (4, 3, '2019-01-02')
INSERT INTO Baratok (FelhID1, FelhID2, BaratsagKezdete) VALUES (6, 7, '2017-12-06')
INSERT INTO Baratok (FelhID1, FelhID2, BaratsagKezdete) VALUES (7, 6, '2017-12-06')
INSERT INTO Baratok (FelhID1, FelhID2, BaratsagKezdete) VALUES (4, 5, '2010-03-12')
INSERT INTO Baratok (FelhID1, FelhID2, BaratsagKezdete) VALUES (5, 4, '2010-03-12')

INSERT INTO OldalTipusok (OldalTipNev) VALUES ('sport')
INSERT INTO OldalTipusok (OldalTipNev) VALUES ('zene')
INSERT INTO OldalTipusok (OldalTipNev) VALUES ('kozmetika')
INSERT INTO OldalTipusok (OldalTipNev) VALUES ('kultura')
INSERT INTO OldalTipusok (OldalTipNev) VALUES ('film')
INSERT INTO OldalTipusok (OldalTipNev) VALUES ('adok-veszek')
INSERT INTO OldalTipusok (OldalTipNev) VALUES ('hir')

INSERT INTO Oldalak (OldalMegnev, IndulasiEv, Weboldal, OldalTipID, Csillag) VALUES ('CitySport', 2017, 'citysport.ro', 1, 2)
INSERT INTO Oldalak (OldalMegnev, IndulasiEv, Weboldal, OldalTipID, Csillag) VALUES ('Kolozsvari opera', 1975, 'huntheater.ro', 4, 4)
INSERT INTO Oldalak (OldalMegnev, IndulasiEv, Weboldal, OldalTipID, Csillag) VALUES ('Double Rise Festival', 2015, 'doublerise.ro', 2, 5)
INSERT INTO Oldalak (OldalMegnev, IndulasiEv, Weboldal, OldalTipID, Csillag) VALUES ('Transindex', 2000, 'transindex.ro', 7, 4)
INSERT INTO Oldalak (OldalMegnev, IndulasiEv, Weboldal, OldalTipID, Csillag) VALUES ('Jazz in the park', 2008, 'jazzinthepark.net', 2, 1)
INSERT INTO Oldalak (OldalMegnev, IndulasiEv, Weboldal, OldalTipID, Csillag) VALUES ('CinemaCity', 2013, 'cinemacity.ro', 5, 3)

INSERT INTO FelhasznaloKedvencei (FelhID, OldalID, KiemeltE) VALUES (1, 1, 0)
INSERT INTO FelhasznaloKedvencei (FelhID, OldalID, KiemeltE) VALUES (5, 3, 1)
INSERT INTO FelhasznaloKedvencei (FelhID, OldalID, KiemeltE) VALUES (5, 5, 0)
INSERT INTO FelhasznaloKedvencei (FelhID, OldalID, KiemeltE) VALUES (2, 3, 1)
INSERT INTO FelhasznaloKedvencei (FelhID, OldalID, KiemeltE) VALUES (2, 5, 0)
INSERT INTO FelhasznaloKedvencei (FelhID, OldalID, KiemeltE) VALUES (4, 2, 1)
INSERT INTO FelhasznaloKedvencei (FelhID, OldalID, KiemeltE) VALUES (6, 4, 0)

INSERT INTO FelhasznaloPosztjai (FelhID, OldalID, Idopont, Leiras) VALUES (2, 4, '2019-11-11', 'Szavazas  eredmenyek...')
INSERT INTO FelhasznaloPosztjai (FelhID, OldalID, Idopont, Leiras) VALUES (3, 4, '2019-11-10', 'Szavazzatok!')
INSERT INTO FelhasznaloPosztjai (FelhID, OldalID, Idopont, Leiras) VALUES (1, 1, '2018-01-11', NULL)
INSERT INTO FelhasznaloPosztjai (FelhID, OldalID, Idopont, Leiras) VALUES (5, 1, '2017-05-06', 'Hajra mindenki!')
INSERT INTO FelhasznaloPosztjai (FelhID, OldalID, Idopont, Leiras) VALUES (5, 3, '2018-10-28', 'Jo ez a szam!')

--Adjuk meg oldaltípusonként, oldalakra lebontva a felhasználók átlagéletkorát, akik az oldalakat kedvelték! (OldalTipusok.OldalTipNev, Oldalak.OldalMegnev, AtlagEletKor)
--SIMA SELECTTEL
SELECT OldalTipusok.OldalTipNev, Oldalak.OldalMegnev, AtlagEletkor
FROM OldalTipusok
LEFT JOIN Oldalak ON Oldalak.OldalTipID=OldalTipusok.OldalTipID
LEFT JOIN (SELECT AVG(YEAR(getdate()) - YEAR(Felhasznalok.SzulDatum)) as AtlagEletkor,Oldalak.OldalID
FROM Felhasznalok
JOIN FelhasznaloKedvencei ON Felhasznalok.FelhID=FelhasznaloKedvencei.FelhID
JOIN Oldalak ON FelhasznaloKedvencei.OldalID=Oldalak.OldalID
GROUP BY Oldalak.OldalID) as AtlagEletkor ON Oldalak.OldalID=AtlagEletkor.OldalID
GROUP BY OldalTipNev,OldalMegnev,AtlagEletkor

--VIEWAL 

--CREATE VIEW Atlagok_View 
--AS
SELECT OldalTipusok.OldalTipNev, Oldalak.OldalMegnev, AtlagEletkor
FROM OldalTipusok
LEFT JOIN Oldalak ON Oldalak.OldalTipID=OldalTipusok.OldalTipID
LEFT JOIN (SELECT AVG(YEAR(getdate()) - YEAR(Felhasznalok.SzulDatum)) as AtlagEletkor,Oldalak.OldalID
FROM Felhasznalok
JOIN FelhasznaloKedvencei ON Felhasznalok.FelhID=FelhasznaloKedvencei.FelhID
JOIN Oldalak ON FelhasznaloKedvencei.OldalID=Oldalak.OldalID
GROUP BY Oldalak.OldalID) as AtlagEletkor ON Oldalak.OldalID=AtlagEletkor.OldalID
GROUP BY OldalTipNev,OldalMegnev,AtlagEletkor;

--GO
--SELECT * FROM Atlagok_View
--DROP VIEW Atlagok_View


--Adjuk meg a legújabban indult oldalak közül, melyekre posztolt a legtöbb felhasználó! Ha a legújabban indult oldalakra még nem posztolt senki, akkor ez a szám legyen 0! (Oldalak.OldalMegnev, PosztokSzama)
SELECT Oldalak.OldalMegnev,PosztokSzama
FROM Oldalak
JOIN (SELECT Oldalak.OldalID,COUNT(FelhasznaloPosztjai.OldalId) as PosztokSzama
FROM Oldalak
LEFT JOIN FelhasznaloPosztjai ON FelhasznaloPosztjai.OldalID=Oldalak.OldalID
GROUP BY Oldalak.OldalID) as valami ON valami.OldalID=Oldalak.OldalID
WHERE Oldalak.IndulasiEv=(SELECT MAX(Oldalak.IndulasiEv) FROM Oldalak)
GROUP BY OldalMegnev,PosztokSzama

--Adjuk meg azon oldalakat, melyekre senki nem posztolt az elmúlt héten! (Oldalak.OldalMegnev, Oldalak.Indulasi

--SELECT * FROM Oldalak
--SELECT * FROM FelhasznaloPosztjai


--Sima SELECT
SELECT Oldalak.OldalMegnev,Oldalak.IndulasiEv
FROM Oldalak
JOIN
(
SELECT Oldalak.OldalID
FROM Oldalak
EXCEPT
SELECT Oldalak.OldalID
FROM Oldalak
LEFT JOIN FelhasznaloPosztjai ON Oldalak.OldalID=FelhasznaloPosztjai.OldalID
WHERE (ABS(DATEDIFF(day,DAY(GETDATE()),DAY(FelhasznaloPosztjai.Idopont))) <= 7)
GROUP BY Oldalak.OldalID) as Eredmeny ON Eredmeny.OldalID=Oldalak.OldalID


--TEMPORARYVAL UGYAN EZ A FELADAT
SELECT Oldalak.OldalMegnev,Oldalak.IndulasiEv
INTO #NemPosztolt
FROM Oldalak
JOIN
(
SELECT Oldalak.OldalID
FROM Oldalak
EXCEPT
SELECT Oldalak.OldalID
FROM Oldalak
LEFT JOIN FelhasznaloPosztjai ON Oldalak.OldalID=FelhasznaloPosztjai.OldalID
WHERE (ABS(DATEDIFF(day,DAY(GETDATE()),DAY(FelhasznaloPosztjai.Idopont))) <= 7)
GROUP BY Oldalak.OldalID) as Eredmeny ON Eredmeny.OldalID=Oldalak.OldalID

SELECT * FROM #NemPosztolt
Drop Table #NemPosztolt

--Adjuk meg felhasználónként a barátai neveit! STRING_AGG függvényt használjunk! 
--Az eredményben a felhasználónév vezeték- és keresztnevét fűzzük össze és mellette jelenítsük meg a barátainak a vezeték- és keresztneveit összefűzve, 
--vesszővel elválasztva! (FelhasznaloNev, BaratokNevei) (Opcionális: úgy oldjuk meg, hogy a barátok nevei csak egyszer jelenjenek meg!)

SELECT * FROM Felhasznalok
SELECT * FROM Baratok
SELECT CONCAT(Felhasznalok.VezetekNev, ' ', Felhasznalok.KeresztNev) AS FelhasznaloNev, Baratok.FelhID1,Baratok.FelhID2
INTO #Profil
FROM Baratok
JOIN Felhasznalok ON Felhasznalok.FelhID=Baratok.FelhID1
GROUP BY Felhasznalok.VezetekNev,Felhasznalok.KeresztNev, Baratok.FelhID1,Baratok.FelhID2

SELECT CONCAT(Felhasznalok.VezetekNev, ' ', Felhasznalok.KeresztNev) AS BaratNev, Baratok.FelhID1,Baratok.FelhID2
INTO #Barat
FROM Baratok
JOIN Felhasznalok ON Felhasznalok.FelhID=Baratok.FelhID2
GROUP BY Felhasznalok.VezetekNev,Felhasznalok.KeresztNev, Baratok.FelhID1,Baratok.FelhID2

SELECT #Profil.FelhasznaloNev,STRING_AGG(#Barat.BaratNev,',') as BaratokNevei
FROM #Profil,#Barat
WHERE #Profil.FelhID1=#Barat.FelhID1
GROUP BY #Profil.FelhasznaloNev

DROP TABLE #Profil
DROP TABLE #Barat


--  Írjunk tárolt eljárást, mely a paraméterként megadott oldal (@pOldalMegnev) posztjainak leírásából eltünteti a felesleges szóközöket! 
--Ellenőrizzük, hogy a bemeneti paraméter értéke ne legyen üres string, ez esetben jelenítsünk meg hibaüzenetet! 
--Csak akkor keressük a felesleges szóközöket, ha a leírás értéke nem NULL, ha NULL, akkor állítsuk át üres stringre: ‘’! 
--UPDATE és CASE utasításokat használjunk! 


--SELECT * FROM Oldalak
--SELECT * FROM FelhasznaloPosztjai

GO
CREATE OR ALTER PROCEDURE Elso(@pOldalMegnev VARCHAR(50))
AS
BEGIN
SET NOCOUNT ON
IF (@pOldalMegnev='')
BEGIN
RAISERROR('Hiba: Ures String',15,1)
RETURN
END
	update FelhasznaloPosztjai
	SET Leiras =  CASE
	  WHEN Leiras is null then ''
	  ELSE replace(Leiras,'  ',' ')
    END
	FROM FelhasznaloPosztjai fp
	JOIN Oldalak o
	ON o.OldalID=fp.OldalID
	WHERE o.OldalMegnev=@pOldalMegnev
END
GO

EXEC Elso 'zene'
SELECT * FROM FelhasznaloPosztjai


--Írjunk tárolt eljárást, melynek bemenő paramétere egy 30-nál kisebb természetes szám (@pSzam). 
--Ha @pSzam>=30 vagy @pSzam<0, írjunk ki megfelelő hibaüzenetet! 
--Ellenkező esetben, írassuk ki azon oldalak megnevezését, amelyek kedvelőinek átlagéletkora kisebb, mint a paraméterként megadott érték!

GO
CREATE OR ALTER PROCEDURE Masodik(@pSzam INT)
AS
BEGIN
SET NOCOUNT ON
IF (@pSzam>=30 OR @pszam<0)
BEGIN
RAISERROR('Hiba: 1-30 kozott kell szerepelnie a szamnak',15,1)
RETURN
END

 SELECT Oldalak.OldalMegnev
	INTO #MasodikTemp
  FROM Oldalak
  JOIN FelhasznaloKedvencei ON Oldalak.OldalID=FelhasznaloKedvencei.OldalID
  JOIN Felhasznalok ON FelhasznaloKedvencei.FelhID=Felhasznalok.FelhID
  GROUP BY Oldalak.OldalMegnev
  HAVING AVG(year(getdate())-Year(Felhasznalok.SzulDatum)) <=@pSzam

SELECT * FROM #MasodikTemp
DROP TABLE #MasodikTemp
END
GO
EXEC Masodik '26'

--Írjunk tárolt eljárást, mely megadja azon felhasználókat, akik a paraméterként megadott típusba (@pOldalTipNev) tartozó minden oldalra posztoltak már legalább 1x! 
--Ha nincs egyetlen oldal sem, amely eleget tenne a feltételeknek, a @pOut kimeneti paraméter értékét állítsuk -1-re, ellenkező esetben 0-ra! 
--Ellenőrizzük, hogy a bemeneti paraméter értéke ne legyen üres string, ez esetben jelenítsünk meg hibaüzenetet!


GO
CREATE OR ALTER PROCEDURE Harmadik(@pOldalTipNev VARCHAR(50))
AS
BEGIN
SET NOCOUNT ON
IF (@pOldalTipNev='')
BEGIN
RAISERROR('Hiba: Ures String',15,1)
RETURN
END
	DECLARE @pOut INT;
	SET @pOut = 0
	
	DECLARE @retVal int
	SELECT @retVal =COUNT(*) FROM
	(
	SELECT Felhasznalok.FelhID
	FROM Felhasznalok
	JOIN FelhasznaloPosztjai ON Felhasznalok.FelhID=FelhasznaloPosztjai.FelhID
	JOIN Oldalak ON FelhasznaloPosztjai.OldalID=Oldalak.OldalID
	JOIN OldalTipusok ON Oldalak.OldalTipID=OldalTipusok.OldalTipID
	WHERE OldalTipusok.OldalTipNev=@pOldalTipNev
	GROUP BY Felhasznalok.FelhID) as src


	IF (@retVal > 0)
	BEGIN

	SELECT Felhasznalok.FelhID
	FROM Felhasznalok
	JOIN FelhasznaloPosztjai ON Felhasznalok.FelhID=FelhasznaloPosztjai.FelhID
	JOIN Oldalak ON FelhasznaloPosztjai.OldalID=Oldalak.OldalID
	JOIN OldalTipusok ON Oldalak.OldalTipID=OldalTipusok.OldalTipID
	WHERE OldalTipusok.OldalTipNev=@pOldalTipNev
	GROUP BY Felhasznalok.FelhID
	END
	
	ELSE
	BEGIN
	 SET @pOut = -1
	END 
	RETURN @pOut
END
GO

DECLARE @return_st int
EXEC @return_st = Harmadik 'hir'
SELECT @return_st as ReturnValue


--Írjunk függvényt, mely kiszámolja egy adott időintervallumon belül született barátságok felhasználóinak átlagéletkorát. 
--Bemeneti paraméterek: @pDatum1, @pDatum2 - dátum típusúak, visszatérítési érték az átlagéletkor, hibás bemenet esetén: -1. 
--Megj. Ellenőrizzük a bemeneti adatok helyességét (pl. @pDatum1 nem lehet későbbi, mint @pDatum2, egyik sem lehet az aktuális dátumnál későbbi stb.)

GO
CREATE OR ALTER FUNCTION Otodik(@pDatum1 DATE,@pDatum2 DATE)
RETURNS INT
BEGIN

IF (@pDatum1>@pDatum2)
BEGIN
--RAISERROR('Hibas datum',15,1)
RETURN -1
END

IF(@pDatum1 > GETDATE())
BEGIN
--RAISERROR('Hibas datum',15,1)
RETURN -1
END

IF(@pDatum2 > GETDATE())
BEGIN
--RAISERROR('Hibas datum',15,1)
RETURN -1
END

DECLARE @pSet INT
SET @pSet = 
(
SELECT AVG(Kora) FROM
(SELECT (YEAR(getdate())-YEAR(Felhasznalok.SzulDatum)) as Kora
FROM Felhasznalok
JOIN Baratok ON (Felhasznalok.FelhID=Baratok.FelhID1) OR (Felhasznalok.FelhID=FelhID2)
WHERE (Baratok.BaratsagKezdete>=@pDatum1) AND (Baratok.BaratsagKezdete<=@pDatum2)
GROUP BY Felhasznalok.SzulDatum) as Datas)

 RETURN @pSet
END
GO

DECLARE @pAsz INT
EXEC @pAsz = Otodik '2005-01-01','2019-05-04'
SELECT @pAsz
DROP FUNCTION IF EXISTS Otodik

