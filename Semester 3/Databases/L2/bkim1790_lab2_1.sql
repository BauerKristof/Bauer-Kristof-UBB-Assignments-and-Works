DROP TABLE IF EXISTS ReszVetel
DROP TABLE IF EXISTS Muveszek
DROP TABLE IF EXISTS Szinpadok
DROP TABLE IF EXISTS Stilusok
DROP TABLE IF EXISTS ReszVetel
DROP TABLE IF EXISTS Jegyek
DROP TABLE IF EXISTS JegyTipusok






CREATE TABLE Szinpadok(
  SzID INT IDENTITY,
  CONSTRAINT PK_SzID PRIMARY KEY(SzID),

  SZNev VARCHAR(28),
  Cim VARCHAR(28),
  )
  
  CREATE TABLE Stilusok(
  StilusID INT IDENTITY,
  CONSTRAINT PK_StilusID PRIMARY KEY(StilusID),

  SNev VARCHAR(28),
  Leiras VARCHAR(100),
 )
  
  CREATE TABLE Muveszek(
  MID INT IDENTITY,
  CONSTRAINT PK_MID PRIMARY KEY(MID),

  MNev VARCHAR(50),
  StilusID INT,
  CONSTRAINT FK_StilusID FOREIGN KEY(StilusID) REFERENCES Stilusok(StilusID),


  SzOrszag VARCHAR(50),
  AlakulasiEv INT,
  SzinpadID INT, 
  CONSTRAINT FK_SzinpadID FOREIGN KEY(SzinpadID) REFERENCES Szinpadok(SZID),
  KoncertNap INT,
  KezdIdopont INT,
)  

 CREATE TABLE JegyTipusok(
  JTID INT IDENTITY,
  CONSTRAINT PK_JTID PRIMARY KEY(JTID),

  JTNev VARCHAR(28),
  Ar REAL,
  )
  
   CREATE TABLE Jegyek(
     JegyKod INT IDENTITY,
	  CONSTRAINT PK_Jegykod PRIMARY KEY(JegyKod),

	 JTID INT,
	 CONSTRAINT FK_JTID FOREIGN KEY(JTID) REFERENCES JegyTipusok(JTID),
	  VasarloEletkor INT,
  )
  
   CREATE TABLE ReszVetel(
	JegyKod INT,
	 MID INT,

  CONSTRAINT FK_JegyKod FOREIGN KEY(JegyKod) REFERENCES Jegyek(JegyKod),
  CONSTRAINT FK_MID FOREIGN KEY(MID) REFERENCES Muveszek(MID),
  CONSTRAINT PK_ReszVetel PRIMARY KEY(JegyKod, MID), --lehet hibas

  );

--1
alter table Muveszek add SzulDatum DateTime DEFAULT '19700101' NOT NULL;
--2
ALTER TABLE Stilusok DROP COLUMN Leiras;
--3
ALTER TABLE Muveszek ADD EmailCim VARCHAR(40);
ALTER TABLE Muveszek ADD CONSTRAINT U_Email UNIQUE(EmailCim);
--4
alter table Muveszek add constraint CHK_KoncertNap check (KoncertNap >= 1 and KoncertNap <= 7);
--5
ALTER TABLE Muveszek DROP COLUMN MNev;
ALTER TABLE Muveszek Add MVezetekNev VARCHAR(40) NOT NULL;
ALTER TABLE Muveszek Add MKeresztNev VARCHAR(40) NOT NULL;


INSERT INTO Szinpadok(SZNev,Cim) values('Foszinpad','Nagyabule');
INSERT INTO Szinpadok(SZNev,Cim) values('Mellekszinpad','Yoabule');
INSERT INTO Szinpadok(SZNev,Cim) values('KisSzinpad','Kicsibule');

INSERT INTO Stilusok(SNev) values('Rap');
INSERT INTO Stilusok(SNev) values('Rock');
INSERT INTO Stilusok(SNev) values('Pop');

INSERT INTO Muveszek(StilusID,SzOrszag,AlakulasiEv,SzinpadID,KoncertNap,KezdIdopont,SzulDatum,EmailCim,MVezetekNev,MKeresztNev) values(1,'UK','1985',3,4,17,'1995-05-03','emai@gmail.com','Valaki','Valami');
INSERT INTO Muveszek(StilusID,SzOrszag,AlakulasiEv,SzinpadID,KoncertNap,KezdIdopont,EmailCim,MVezetekNev,MKeresztNev) values(1,'RO','1975',1,5,4,'asf@gmail.com','Alig','Elek');
INSERT INTO Muveszek(StilusID,SzOrszag,AlakulasiEv,SzinpadID,KoncertNap,KezdIdopont,SzulDatum,EmailCim,MVezetekNev,MKeresztNev) values(1,'HUN','2008',2,6,21,'2001-05-04','kicsivagyok@gmail.com','Kicsivagyok','Hamegnovokbeledrugok');

INSERT INTO JegyTipusok(JTNev,Ar) values('Early Bird',2500.50);
INSERT INTO JegyTipusok(JTNev,Ar) values('Normal',5100.50);
INSERT INTO JegyTipusok(JTNev,Ar) values('VIP',90000.125);

INSERT INTO Jegyek(JTID,VasarloEletkor) values(1,18);
INSERT INTO Jegyek(JTID,VasarloEletkor) values(2,20);
INSERT INTO Jegyek(JTID,VasarloEletkor) values(3,22);

INSERT INTO ReszVetel(JegyKod,MID) values (1,3);
INSERT INTO ReszVetel(JegyKod,MID) values (2,1);
INSERT INTO ReszVetel(JegyKod,MID) values (1,1);



select * from Szinpadok;
select * from Stilusok;
select * from Muveszek;
select * from JegyTipusok;
select * from Jegyek;
select * from ReszVetel;