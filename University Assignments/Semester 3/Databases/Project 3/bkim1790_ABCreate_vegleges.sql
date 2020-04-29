USE master;
GO

IF EXISTS(select * from sys.databases where name='bkim1790_sajat4')
	DROP DATABASE bkim1790_sajat4

CREATE DATABASE bkim1790_sajat4;
GO

USE bkim1790_sajat4;
GO

CREATE TABLE Soforok(
 -- SfID INT PRIMARY KEY IDENTITY,
 --  SfID INT IDENTITY,
   SfID INT,
   CONSTRAINT PK_SfID PRIMARY KEY(SfID),

  SfNeve VARCHAR(28),
  SfFizetes REAL,
  )
  
  CREATE TABLE Autok(
  --AID INT PRIMARY KEY IDENTITY,
  AID INT IDENTITY,
  CONSTRAINT PK_AID PRIMARY KEY(AID),
  Tipus VARCHAR(28),
  )

  CREATE TABLE Vezeti(
  	SfID INT,
	AID INT,

  CONSTRAINT FK_SfID FOREIGN KEY(SfID) REFERENCES Soforok(SfID),
  CONSTRAINT FK_AID FOREIGN KEY(AID) REFERENCES Autok(AID),
  CONSTRAINT PK_Vezeti PRIMARY KEY(SfID, AID)
  )


  CREATE TABLE SzallitoCegek(
  --  SzID INT PRIMARY KEY IDENTITY,
   --SzID INT IDENTITY,
   SzID INT
   CONSTRAINT PK_SzID PRIMARY KEY(SzID),
   SzNev VARCHAR(28),
 )

CREATE TABLE Alkalmazott(
  	SfID INT,
	SzID INT,

  CONSTRAINT FK_SfIDAlk FOREIGN KEY(SfID) REFERENCES Soforok(SfID),
  CONSTRAINT FK_SzID FOREIGN KEY(SzID) REFERENCES SzallitoCegek(SzID),
  CONSTRAINT PK_Alkalmazott PRIMARY KEY(SfID, SzID)
  )

  
  CREATE TABLE Internetescegek(
  --IcID INT PRIMARY KEY IDENTITY,
    IcID INT IDENTITY,
   CONSTRAINT PK_IcID PRIMARY KEY(IcID),
    IcNeve VARCHAR(50),
)  


CREATE TABLE Kuldet(
	SzID INT,
    IcID INT,
	KuldDatum DATE,

  CONSTRAINT FK_IcID FOREIGN KEY(IcID) REFERENCES Internetescegek(IcID),
  CONSTRAINT FK_SzIDKuld FOREIGN KEY(SzID) REFERENCES SzallitoCegek(SzID),
  CONSTRAINT PK_Kuldet PRIMARY KEY(SzID,IcID)
  )

 CREATE TABLE Termekek(
  --TID INT PRIMARY KEY IDENTITY,
  TID INT IDENTITY,
  CONSTRAINT PK_TID PRIMARY KEY(TID),
  TAr REAL,
  TNeve VARCHAR(40),

  )
  
CREATE TABLE Elad(
	IcID INT,
    TID INT,
	EladDatum DATE,

  CONSTRAINT FK_IcIDEl FOREIGN KEY(IcID) REFERENCES Internetescegek(IcID),
  CONSTRAINT FK_TID FOREIGN KEY(TID) REFERENCES Termekek(TID),
  CONSTRAINT PK_Elad PRIMARY KEY(IcID,TID)
  )

  CREATE TABLE Vevok(
     --VID INT PRIMARY KEY IDENTITY,
	-- VID INT IDENTITY,
	 VID INT,
	 CONSTRAINT PK_VID PRIMARY KEY(VID),
	 VNeve VARCHAR(28),
   )

 CREATE TABLE Szallit(
	SfID INT,
    VID INT,

  CONSTRAINT FK_SfIdSzal FOREIGN KEY(SfID) REFERENCES Soforok(SfID),
  CONSTRAINT FK_VID FOREIGN KEY(VID) REFERENCES Vevok(VID),
  CONSTRAINT PK_Szallit PRIMARY KEY(SfID,VID)
  )

CREATE TABLE Vasarol(
	VID INT,
    TID INT,
	VasarolDatum DATE,

  CONSTRAINT FK_VIDEl FOREIGN KEY(VID) REFERENCES Vevok(VID),
  CONSTRAINT FK_TIDEl FOREIGN KEY(TID) REFERENCES Termekek(TID),
  CONSTRAINT PK_Vasarol PRIMARY KEY(TID,VID)
  )






 --1. A táblák mezőihez rendeljünk hozzá megfelelő megszorításokat (pl. CHECK megszorítás egy attribútumra, mely egy intervallumból veheti az értékeit, UNIQUE megszorítás a névre (elnevezésekre) stb.).
 --Az ily módon létrehozott s a már létező megszorításoknak (PRIMARY KEY illetve FOREIGN KEY megszorítások) is nevet kell adni (PK és FK elnevezéseit a CREATE TABLE utasításba is betehetitek). 
 --Teljes pontra: minden megszorításból legalább egy hozzáadása valamely táblaszerkezethez.
ALTER TABLE SzallitoCegek ADD CONSTRAINT df_SzNev DEFAULT 'Ismeretlen ceg' FOR SzNev;
ALTER TABLE Kuldet ADD CONSTRAINT dF_Kuldet DEFAULT getdate() FOR KuldDatum
ALTER TABLE Internetescegek ALTER COLUMN IcNeve VARCHAR(50) NOT NULL;
ALTER TABLE Elad ADD CONSTRAINT chk_EladDatum CHECK (EladDatum<=getdate());
ALTER TABLE Termekek ADD CONSTRAINT chk_TAr CHECK (TAr>=0);
ALTER TABLE Vasarol ADD CONSTRAINT chk_VasarolDatum CHECK (VasarolDatum<=getdate());
ALTER TABLE Soforok ADD CONSTRAINT chk_sfFizetes CHECK (sfFizetes>=1325);
ALTER TABLE Autok ADD CONSTRAINT uni_Tipus UNIQUE (Tipus);

INSERT INTO SzallitoCegek(SzID,SzNev) values(1,'Urgent Cargus');
INSERT INTO SzallitoCegek(SzID,SzNev) values(2,'Fan Courier');
INSERT INTO SzallitoCegek(SzID,SzNev) values(3,'Funny Courier');

INSERT INTO SzallitoCegek(SzID) values(4);

INSERT INTO InternetesCegek(IcNeve) values ('Emag');
INSERT INTO InternetesCegek(IcNeve) values ('Carturesti');
INSERT INTO InternetesCegek(IcNeve) values ('Nagy Imre sorozoje');

--INSERT INTO Internetescegek(IcNeve) values (NULL);

INSERT INTO Kuldet(SzID,IcID) values(1,1)
INSERT INTO Kuldet(SzID,IcID) values(2,1)
INSERT INTO Kuldet(SzID,IcID) values(2,2)





INSERT INTO Termekek(TNeve,TAr) values ('Porszivo',120);
INSERT INTO Termekek(TNeve,TAr) values ('RobotPorszivo',120);
INSERT INTO Termekek(TNeve,TAr) values ('Ablaktorlo',50);
--INSERT INTO Termekek(TAr) values (-5);

INSERT INTO Elad(IcID,TID,EladDatum) values (1,1,'20170503');
--INSERT INTO Elad(IcID,TID,EladDatum) values (1,1,'20200503');

INSERT INTO Vevok(VID,VNeve) values (1,'Kiss Beatrix');
INSERT INTO Vevok(VID,VNeve) values (2,'Nagy Ferenc');
INSERT INTO Vevok(VID,VNeve) values (3,'Pap Laszlone');


--INSERT INTO Vevok(Rendelesek) values ('Ablaktorlo');

INSERT INTO Soforok(SfID,SfNeve,SfFizetes) values (1,'Kiss Bela',2000);
INSERT INTO Soforok(SfID,SfNeve,SfFizetes) values (2,'Nagy Agnes',3500);
INSERT INTO Soforok(SfID,SfNeve,SfFizetes) values (3,'Josofor Geza',1325);


--INSERT INTO Soforok(SfNeve,SfFizetes) values ('Nagy Bela',200);

INSERT INTO Autok(Tipus) values ('Opel');
INSERT INTO Autok(Tipus) values ('Ford');
INSERT INTO Autok(Tipus) values ('BMW');


--INSERT INTO Autok(Tipus) values ('Opel');

INSERT INTO Vezeti(SfID,AID) values(1,1);
INSERT INTO Vezeti(SfID,AID) values(2,1);
INSERT INTO Vezeti(SfID,AID) values(3,2);


INSERT INTO Vasarol(VID,TID) values (1,1);
INSERT INTO Vasarol(VID,TID) values (1,2);
INSERT INTO Vasarol(VID,TID) values (2,1);
INSERT INTO Vasarol(VID,TID) values (3,3);








SELECT * FROM SzallitoCegek
SELECT * FROM Kuldet
SELECT * FROM Elad
SELECT * FROM Termekek
SELECT * FROM Vevok
SELECT * FROM Soforok
SELECT * FROM Autok