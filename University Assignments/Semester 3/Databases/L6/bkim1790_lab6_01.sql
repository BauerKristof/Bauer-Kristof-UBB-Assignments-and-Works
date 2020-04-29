USE master;
GO

IF EXISTS(select * from sys.databases where name='Lab6_1')
	DROP DATABASE Lab6_1

SET DATEFORMAT YMD

CREATE DATABASE Lab6_1;
GO

USE Lab6_1;
GO

DROP TABLE IF EXISTS Reszvetel
DROP TABLE IF EXISTS Jegyek
DROP TABLE IF EXISTS Muveszek
DROP TABLE IF EXISTS Szinpadok
DROP TABLE IF EXISTS Stilusok
DROP TABLE IF EXISTS JegyTipusok

CREATE TABLE Szinpadok(
    SzID INT IDENTITY,
	SzNev VARCHAR(50), 
	Cim VARCHAR(50),
	CONSTRAINT PK_Szinpadok PRIMARY KEY (SzID)
)

CREATE TABLE Stilusok(
	StilusID INT IDENTITY,
	SNev VARCHAR(50),
	Leiras VARCHAR(250),
	CONSTRAINT PK_Stilusok PRIMARY KEY (StilusID)
)

CREATE TABLE Muveszek(
    MID INT IDENTITY,
	MVezetekNev VARCHAR(50),
	MKeresztNev VARCHAR(50),
	StilusID INT,
	SzOrszag VARCHAR(50),
	AlakulasiEv INT,
	SzinpadID INT,
	KoncertNap INT,
	KezdoIdopont INT,
	SzulDatum DATE,
	EmailCim VARCHAR(50),
	Honorarium INT,
	CONSTRAINT PK_Muveszek PRIMARY KEY (MID),
	CONSTRAINT FK_Muveszek_Stilusok FOREIGN KEY (StilusID) REFERENCES Stilusok(StilusID),
	CONSTRAINT FK_Muveszek_Szinpadok FOREIGN KEY (SzinpadID) REFERENCES Szinpadok(SzID)
)

CREATE TABLE JegyTipusok(
	JTID INT IDENTITY,
	JTNev VARCHAR(50),
	Ar REAL,
	CONSTRAINT PK_JegyTipusok PRIMARY KEY (JTID)
)

CREATE TABLE Jegyek(
    JegyKod INT IDENTITY,
	JTID INT,
	VasarloEletkor INT,
	CONSTRAINT PK_Jegyek PRIMARY KEY (JegyKod),
    CONSTRAINT FK_Jegyek_JegyTipusok FOREIGN KEY (JTID) REFERENCES JegyTipusok(JTID) --4.A-HOZ KOMMENTELD BE!!!
)

CREATE TABLE Reszvetel(
    JegyKod INT,
	MID INT,
	CONSTRAINT PK_Reszvetel PRIMARY KEY (JegyKod, MID),
	CONSTRAINT FK_Reszvetel_Jegyek FOREIGN KEY (JegyKod) REFERENCES Jegyek(JegyKod),
	CONSTRAINT FK_Reszvetel_Muveszek FOREIGN KEY (MID) REFERENCES Muveszek(MID)	
)

--4. a. Hozzunk létre egy új táblát:
  --JegytipusArak_Log (Idopont, Muvelet, JTID, JTNev, RegiAr, UjAr),

CREATE TABLE JegytipusArak_Log (
	Idopont DATETIME,
	Muvelet varchar(50),
	RegiAr INT,
	UjAr INT,
	JTID INT,
	JTNev Varchar(50),
    CONSTRAINT FK_JegyTipusArak_Log FOREIGN KEY (JTID) REFERENCES JegyTipusok(JTID) --4.A TRIGGERHEZ KOMMENTELD BE!!!
)

INSERT INTO Szinpadok (SzNev, Cim) VALUES ('Main Square', 'Main street 3')
INSERT INTO Szinpadok (SzNev, Cim) VALUES ('Backstage', '5th Ave')
INSERT INTO Szinpadok (SzNev, Cim) VALUES ('Cluj Arena', 'Aleea Stadionului 2')
INSERT INTO Szinpadok (SzNev, Cim) VALUES ('BT Arena', 'Aleea Stadionului 3')

INSERT INTO Stilusok (SNev, Leiras) VALUES ('rock', 'rock stilus')
INSERT INTO Stilusok (SNev, Leiras) VALUES ('pop', 'pop stilus')
INSERT INTO Stilusok (SNev, Leiras) VALUES ('techno', 'techno stilusu zene')
INSERT INTO Stilusok (SNev, Leiras) VALUES ('hip-hop', 'hip-hop stilus')
INSERT INTO Stilusok (SNev, Leiras) VALUES ('classical', 'klasszikus zene')

INSERT INTO Muveszek (MVezetekNev, MKeresztNev, StilusID, SzOrszag, AlakulasiEv, SzinpadID, KoncertNap, KezdoIdopont, SzulDatum, EmailCim, Honorarium) VALUES 
	('Adams', 'Brian',  2, 'Canada', 1984, 1, 1, 20, '1959-11-05', 'brian@gmail.com', 5000),
	('Iglesias', 'Enrique', 2, 'Spain', 1995, 2, 3, 21, '1975-05-08', 'enrique@hotmail.com', 6000),
	('Dion', 'Celine', 5, 'Canada', 1988, 2, 4, 20, '1968-11-05', 'celine@gmail.com', 7000),
	('Walker', 'Alan', 3, 'Norway', 2015, 3, 1, 23, '1999-08-24', 'alan@gmail.com', 4000),
	('Garrix', 'Martin', 3, 'The Netherlands', 2016, 3, 2, 22, '2000-05-12', 'martin@gmail.com', 5000),
	('Rita', 'Ora', 2, 'Serbia', 2013, 3, 2, 19, '1990-11-26', 'rita@yahoo.com', 3000)

INSERT INTO JegyTipusok (JTNev, Ar) VALUES ('Early bird', 50)
INSERT INTO JegyTipusok (JTNev, Ar) VALUES ('VIP', 150)
INSERT INTO JegyTipusok (JTNev, Ar) VALUES ('Floor', 75)
INSERT INTO JegyTipusok (JTNev, Ar) VALUES ('Seats', 90)

select * from JegytipusArak_Log

INSERT INTO Jegyek (JTID, VasarloEletkor) VALUES (1, 21)
INSERT INTO Jegyek (JTID, VasarloEletkor) VALUES (1, 25)
INSERT INTO Jegyek (JTID, VasarloEletkor) VALUES (1, 32)
INSERT INTO Jegyek (JTID, VasarloEletkor) VALUES (1, 19)
INSERT INTO Jegyek (JTID, VasarloEletkor) VALUES (2, 33)
INSERT INTO Jegyek (JTID, VasarloEletkor) VALUES (2, 23)
INSERT INTO Jegyek (JTID, VasarloEletkor) VALUES (3, 18)
INSERT INTO Jegyek (JTID, VasarloEletkor) VALUES (3, 19)
INSERT INTO Jegyek (JTID, VasarloEletkor) VALUES (3, 24)
INSERT INTO Jegyek (JTID, VasarloEletkor) VALUES (3, 25)
INSERT INTO Jegyek (JTID, VasarloEletkor) VALUES (3, 25)

INSERT INTO Reszvetel (JegyKod, MID) VALUES (1,1)
INSERT INTO Reszvetel (JegyKod, MID) VALUES (1,2)
INSERT INTO Reszvetel (JegyKod, MID) VALUES (1,3)
INSERT INTO Reszvetel (JegyKod, MID) VALUES (2,3)
INSERT INTO Reszvetel (JegyKod, MID) VALUES (2,4)
INSERT INTO Reszvetel (JegyKod, MID) VALUES (3,3)
INSERT INTO Reszvetel (JegyKod, MID) VALUES (4,5)
INSERT INTO Reszvetel (JegyKod, MID) VALUES (4,4)
INSERT INTO Reszvetel (JegyKod, MID) VALUES (5,3)
INSERT INTO Reszvetel (JegyKod, MID) VALUES (6,3)
INSERT INTO Reszvetel (JegyKod, MID) VALUES (7,4)
INSERT INTO Reszvetel (JegyKod, MID) VALUES (8,3)



--1. a. Szúrjuk be a Kedveltseg mezőt a Muveszek táblába, ahol Kedveltseg-INT típusú mező, 0-5 közötti értékeket vehet fel, alapértelmezés szerinti értéke 0.


ALTER TABLE Muveszek ADD Kedveltseg INT DEFAULT 0

--b. Írjunk tárolt eljárást, mely minden művész esetén beállítja a Kedveltseg mező értékét a koncertjén részt vevők száma alapján:

GO
CREATE PROCEDURE KedveltsegBeallit
AS 
BEGIN
SET NOCOUNT ON;  

SELECT Muveszek.MID,COUNT(Reszvetel.MID) as ResztvevoSzam
INTO #ResztvevokSzama
FROM Muveszek
LEFT JOIN Reszvetel ON Reszvetel.MID=Muveszek.MID
GROUP BY Muveszek.MID


  
DECLARE @M_id int, @resztvevok_szama int,  
    @kedveltseg int;
  
  
DECLARE A_cursor CURSOR FOR   
SELECT #ResztvevokSzama.MID,#ResztvevokSzama.ResztvevoSzam FROM #ResztvevokSzama

  
OPEN A_cursor  
  
FETCH NEXT FROM A_cursor INTO @M_id, @resztvevok_szama
  
WHILE @@FETCH_STATUS = 0  
BEGIN    
	PRINT '1.A_cursor MID'
	PRINT @M_id
	PRINT '2. A_cursor ResztvevokSzama'
	PRINT @resztvevok_szama
   
   DECLARE B_cursor CURSOR FOR   
    SELECT Muveszek.MID
    FROM Muveszek 
    WHERE Muveszek.MID= @M_id  -- Variable value from the outer cursor  
  
    OPEN B_cursor  
    FETCH NEXT FROM B_cursor INTO @kedveltseg  
  
  
	 WHILE @@FETCH_STATUS = 0  
		BEGIN  
		PRINT '3.B cursor MID: '
		PRINT @kedveltseg
		PRINT '4.B cursors resztvevokSzama'
		PRINT @resztvevok_szama

	
		IF @resztvevok_szama <= 100
		begin
		  UPDATE Muveszek SET Kedveltseg=1
		  WHERE Muveszek.MID=@M_id
		end
		ELSE IF @resztvevok_szama > 100 AND @resztvevok_szama<=500
		  	begin
		 UPDATE Muveszek SET Kedveltseg=2
		  WHERE Muveszek.MID=@M_id
		end
		ELSE IF @resztvevok_szama > 500 AND @resztvevok_szama<=1000
		  	begin
		 UPDATE Muveszek SET Kedveltseg=3
		  WHERE Muveszek.MID=@M_id
		end
		ELSE IF @resztvevok_szama > 1000 AND @resztvevok_szama<=5000
		  	begin
		 UPDATE Muveszek SET Kedveltseg=4
		  WHERE Muveszek.MID=@M_id
		end
		ELSE IF @resztvevok_szama > 5000
		  	begin
		 UPDATE Muveszek SET Kedveltseg=5
		  WHERE Muveszek.MID=@M_id
		end


        FETCH NEXT FROM B_cursor INTO @kedveltseg 
        END  
  
    CLOSE B_cursor  
    DEALLOCATE B_cursor  
        -- Get the next vendor.  
    FETCH NEXT FROM A_cursor  INTO @M_id, @resztvevok_szama 
END   
CLOSE A_cursor;  
DEALLOCATE A_cursor
DROP TABLE #ResztvevokSzama


END
GO

EXEC KedveltsegBeallit

--2. Írjunk DELETE triggert, mely a Reszvetel táblából való törlés esetén aktualizálja a Muveszek tábla Kedveltseg mezőjének értékét!
--Fontos! Nem elfogadott megoldás: ha a triggeren belül egyszerűen csak meghívjuk az 1-es feladatban megírt tárolt eljárást!
--Megj. Feltételezzük, hogy egyszerre csak egy sort törlünk!

GO
CREATE TRIGGER KedveltsegTrigger ON Reszvetel
AFTER DELETE
AS 
BEGIN

SET NOCOUNT ON
DECLARE @M_ID INT
SET @M_ID = (SELECT MID FROM deleted)

SELECT Muveszek.MID,COUNT(Reszvetel.MID) as ResztvevoSzam
INTO #Resztvevok
FROM Muveszek
LEFT JOIN Reszvetel ON Reszvetel.MID=Muveszek.MID
GROUP BY Muveszek.MID
SELECT * FROM #Resztvevok

 DECLARE @resztvevokSzama INT

 SET @resztvevokSzama=(
	SELECT #Resztvevok.ResztvevoSzam
	FROM #Resztvevok
	WHERE @M_ID=#Resztvevok.MID)

	PRINT 'MID'
	PRINT @M_ID

	PRINT 'RESZTVEVOKSZAMA='
	PRINT @resztvevokSzama

	IF @resztvevokSzama <=100
		begin
		  UPDATE Muveszek SET Kedveltseg=1
		  --		  UPDATE Muveszek SET Kedveltseg=0

		  WHERE Muveszek.MID=@M_ID
		end
		ELSE IF @resztvevokSzama > 100 AND @resztvevokSzama<=500
		  	begin
		 UPDATE Muveszek SET Kedveltseg=2
		  WHERE Muveszek.MID=@M_ID
		end
		ELSE IF @resztvevokSzama > 500 AND @resztvevokSzama<=1000
		  	begin
		 UPDATE Muveszek SET Kedveltseg=3
		  WHERE Muveszek.MID=@M_ID
		end
		ELSE IF @resztvevokSzama > 1000 AND @resztvevokSzama<=5000
		  	begin
		 UPDATE Muveszek SET Kedveltseg=4
		  WHERE Muveszek.MID=@M_ID
		end
		ELSE IF @resztvevokSzama > 5000
		  	begin
		 UPDATE Muveszek SET Kedveltseg=5
		  WHERE Muveszek.MID=@M_ID
		end


DROP TABLE #Resztvevok
END
GO


--SELECT * FROM Muveszek
--DELETE FROM Reszvetel WHERE MID=1;
--SELECT * FROM Muveszek


--3. Írjunk INSERT- és DELETE triggert, mely a Muveszek táblába való beszúrás/törlést csak akkor engedélyezi, ha 
--insert trigger esetén: az adott időpontban (és se előtte se utána 1 órával) nincs más koncert felvezetve az adatbázisba és aznap az adott színpadon kevesebb, mint 5 előadó lép fel;
--delete trigger esetén -  aznap az adott színpadon min 1 előadó fel fog lépni (a törlendő művészen kívül!
--Megj. Feltételezzük, hogy egyszerre csak egy sort szúrunk be/törlünk!


--INSERT
SELECT * FROM Muveszek

GO
CREATE TRIGGER MuveszInsert ON Muveszek
FOR INSERT
AS 
BEGIN

SET NOCOUNT ON
DECLARE @M_ID INT, @K_IDOPONT INT, @K_NAP INT, @HanyEloado INT,@Szinpad_ID INT
SET @M_ID = (SELECT MID FROM inserted)
SET @K_IDOPONT = (SELECT KezdoIdopont FROM inserted)
SET @K_NAP= (SELECT KoncertNap FROM inserted)
SET @Szinpad_ID= (SELECT SzinpadID FROM inserted)

IF @K_IDOPONT IS NULL
RAISERROR('ERROR: NULL VALUE - KezdoIdopont',0,1)
IF @K_NAP IS NULL
RAISERROR('ERROR: NULL VALUE - Kezdeti Nap',0,1)
IF @Szinpad_ID IS NULL
RAISERROR('ERROR: NULL VALUE - SzinpadID',0,1)



SET @HanyEloado=
(
 SELECT COUNT(Muveszek.MID) 
 FROM Muveszek
 WHERE (Muveszek.MID <> @M_ID) AND (Muveszek.KoncertNap = @K_NAP) AND ((ABS(Muveszek.KezdoIdopont-@K_IDOPONT)) <1) AND (Muveszek.SzinpadID=@Szinpad_ID)
)
PRINT @HanyEloado

IF @HanyEloado <5
ROLLBACK TRAN

END
GO



--INSERT Muveszek(MKeresztNev,MVezetekNev) VALUES ('Nagy','Pista')
--SELECT * FROM Muveszek


--DELETE
GO
CREATE TRIGGER MuveszTorolTrigger ON Muveszek
AFTER DELETE
AS 
BEGIN

SET NOCOUNT ON
DECLARE @M_ID INT,@SZINPAD_ID INT,@K_NAP INT, @HanyEloado INT

SET @M_ID = (SELECT MID FROM deleted)
SET @SZINPAD_ID= (SELECT SzinpadID FROM deleted)
SET @K_NAP= (SELECT KoncertNap FROM deleted)

IF @M_ID IS NULL
RAISERROR('ERROR: NULL VALUE - MID',0,1)
IF @K_NAP IS NULL
RAISERROR('ERROR: NULL VALUE - Kezdeti Nap',0,1)
IF @Szinpad_ID IS NULL
RAISERROR('ERROR: NULL VALUE - SzinpadID',0,1)


SET @HanyEloado=
(
 SELECT COUNT(Muveszek.MID) 
 FROM Muveszek
 WHERE (Muveszek.MID <> @M_ID) AND (Muveszek.KoncertNap = @K_NAP) AND (Muveszek.SzinpadID=@SZINPAD_ID)
)

 IF @HanyEloado=0
 ROLLBACK TRAN
 
END
GO

/*DELETE FROM Reszvetel WHERE Reszvetel.MID=1
DELETE FROM Muveszek WHERE Muveszek.MID=1
SELECT * FROM Muveszek*/

DELETE FROM Reszvetel WHERE Reszvetel.MID=5
DELETE FROM Muveszek WHERE Muveszek.MID=5
SELECT * FROM Muveszek


--4a.JTID - a Jegytipusok táblából való törlés esetén értéke NULL-ra módosuljon. 
--(A JTNev-varchar(50) mezőben tároljuk a jegytípus nevét, ha törlünk ebből a táblából és az ID-t NULL-ra állítottuk, akkor a név mezőben loggolva marad a törölt jegytípus neve.)
GO
CREATE TRIGGER JTDeleteTrigger ON JegyTipusok
FOR DELETE
AS 
BEGIN
SET NOCOUNT ON
		SELECT * INTO #RegiAdatok FROM deleted
		SELECT #RegiAdatok.JTID,#RegiAdatok.JTNev INTO #SortedTable FROM #RegiAdatok
		
		DECLARE @JT_ID INT,@JT_Neve VARCHAR(50)
	
	
	DECLARE A_cursor CURSOR FOR   
	SELECT #SortedTable.JTID,#SortedTable.JTNev FROM #SortedTable

	OPEN A_cursor  
		FETCH NEXT FROM A_cursor INTO @JT_ID, @JT_Neve
				WHILE @@FETCH_STATUS = 0  
				BEGIN    
				  --JegytipusArak_Log (Idopont, Muvelet, JTID, JTNev, RegiAr, UjAr),

				 UPDATE JegytipusArak_Log
				 SET JegytipusArak_Log.JTID = NULL, JegyTipusArak_Log.JTNev = @JT_Neve
				 WHERE @JT_ID=JegyTipusArak_Log.JTID;
				 
				 FETCH NEXT FROM A_cursor INTO @JT_ID,@JT_Neve
				 END   
	CLOSE A_cursor;  
	DEALLOCATE A_cursor
DROP TABLE #RegiAdatok
DROP TABLE #SortedTable

END
GO


--4b. Írjunk UPDATE triggert, mely a JegyTipusok tábla Ar mezőjének módosításakor beszúr egy új sort a JegytipusArak_Log táblába. 
--Az időpont legyen a módosítás időpontja, művelet szövege: ‘ár növelése’ vagy ‘ár csökkentése’, RegiAr-régi érték, UjAr-új érték.
--Megj. Oldjuk meg a feladatot feltételezve, hogy egyszerre több sort módosíthatunk a táblában! 

  --JegytipusArak_Log (Idopont, Muvelet, JTID, JTNev, RegiAr, UjAr),



GO
CREATE TRIGGER JTTrigger ON JegyTipusok
FOR UPDATE
AS 
BEGIN
SET NOCOUNT ON
	IF UPDATE(Ar)
	BEGIN
	SELECT * INTO #RegiAdatok FROM deleted
	SELECT * INTO #UjAdatok FROM inserted

	SELECT #RegiAdatok.JTID, #RegiAdatok.Ar as RegiAr,#UjAdatok.Ar as UjAr,#RegiAdatok.JTNev,GETDATE() as ModositasDatum
	INTO #FinalTable
	FROM #RegiAdatok,#UjAdatok
	WHERE (#RegiAdatok.JTID=#UjAdatok.JTID) AND (#RegiAdatok.Ar <> #UjAdatok.Ar)


	DECLARE @JT_ID INT,@Regi_Ar INT,@Uj_Ar INT,@M_Datum DATETIME,@JT_Neve VARCHAR(50)
	DECLARE A_cursor CURSOR FOR   
	SELECT #FinalTable.JTID, #FinalTable.RegiAr,#FinalTable.UjAr,#FinalTable.ModositasDatum,#FinalTable.JTNev FROM #FinalTable

	OPEN A_cursor  
		FETCH NEXT FROM A_cursor INTO @JT_ID, @Regi_Ar,@Uj_Ar,@M_Datum,@JT_Neve
				WHILE @@FETCH_STATUS = 0  
				BEGIN    
				  --JegytipusArak_Log (Idopont, Muvelet, JTID, JTNev, RegiAr, UjAr),
				  IF @Regi_Ar<@Uj_Ar
				 INSERT INTO JegytipusArak_Log(Idopont, Muvelet,JTID,JTNev,RegiAr,UjAr) VALUES(@M_Datum,'ar novelese',@JT_ID,@JT_Neve,@Regi_Ar,@Uj_Ar)
				 
				 ELSE INSERT INTO JegytipusArak_Log(Idopont, Muvelet,JTID,JTNev,RegiAr,UjAr) VALUES(@M_Datum,'ar csokkenese',@JT_ID,@JT_Neve,@Regi_Ar,@Uj_Ar)
				 
				 FETCH NEXT FROM A_cursor INTO @JT_ID, @Regi_Ar,@Uj_Ar,@M_Datum,@JT_Neve
				 END   
	CLOSE A_cursor;  
	DEALLOCATE A_cursor



	DROP TABLE #RegiAdatok
	DROP TABLE #UjAdatok
	DROP TABLE #FinalTable
	END
END
GO

UPDATE JegyTipusok SET Ar=500 WHERE JegyTipusok.JTID=1 OR JegyTipusok.JTID=2
UPDATE JegyTipusok SET Ar=50 WHERE JegyTipusok.JTID=1

UPDATE JegyTipusok SET JTNev='Teszt' WHERE JegyTipusok.JTID=3

SELECT * FROM JegytipusArak_Log



DELETE FROM JegyTipusok WHERE JegyTipusok.JTID=1;
SELECT * FROM JegytipusArak_Log
