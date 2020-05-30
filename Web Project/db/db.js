// Adatbázis műveleteket végző modul

const mysql = require('mysql');

// Létrehozunk egy connection poolt
const pool = mysql.createPool({
  connectionLimit: 10,
  database: 'mydb',
  host: 'localhost',
  port: 3306,
  user: 'root',
  password: 'server',
});

const queryFunction = (query, options = []) => new Promise((resolve, reject) => {
  pool.query(query, options, (error, results) => {
    if (error) {
      reject(new Error(`Error while running '${query}: ${error}'`));
    }
    resolve(results);
  });
});

// /TODO:String ISBN
pool.query(`CREATE TABLE IF NOT EXISTS konyv (
  ISBN varchar(50), 
  Cim varchar(30),
  Szerzo varchar(30),
  Osszefoglalo varchar(50),
  Boritokep varchar(250),
  Peldanyszam INT,
  primary key(ISBN)
  );`, (err) => {
  if (err) {
    console.error(`Create konyv table error: ${err}`);
    process.exit(1);
  } else {
    console.log('Konyv Table created successfully');
  }
});

pool.query('CREATE TABLE IF NOT EXISTS felhasznalo (Nev varchar(50), primary key(Nev));', (err) => {
  if (err) {
    console.error(`Create Felhasznalo table error: ${err}`);
    process.exit(1);
  } else {
    console.log('Felhasznalo Table created successfully');
  }
});

pool.query('CREATE TABLE IF NOT EXISTS kolcsonzes (KNev varchar(50),KISBN varchar(50),FOREIGN KEY (KNev) REFERENCES felhasznalo(Nev),FOREIGN KEY (KISBN) REFERENCES konyv(ISBN));', (err) => {
  if (err) {
    console.error(`Create Kolcsonzes table error: ${err}`);
    process.exit(1);
  } else {
    console.log('kolcsonzes Table created successfully');
  }
});


pool.query('CREATE TABLE IF NOT EXISTS loginfelhasznalok (Felhasznalonev varchar(200),Jelszo varchar(500),Jogkor varchar(15));', (err) => {
  if (err) {
    console.error(`Create loginfelhasznalok table error: ${err}`);
    process.exit(1);
  } else {
    console.log('loginfelhasznalok Table created successfully');
  }
});


exports.insertBook = (req, callback) => {
  const { isbnNumber } = req;
  const { bookTitle } = req;
  const { bookAuthor } = req;
  const { bookDescription } = req;
  const coverPhoto = req.bookCoverPath;
  const { bookNumber } = req;

  const query = `insert into konyv(ISBN,Cim,Szerzo,Osszefoglalo,Boritokep,PeldanySzam) 
  VALUES("${isbnNumber}","${bookTitle}","${bookAuthor}","${bookDescription}","${coverPhoto}",${bookNumber});`;
  pool.query(query, callback);
};

// -----------konyv-----------------
// service metódus - lekéri az összes konyv infot
exports.getBooks = (callback) => {
  const query = 'SELECT * FROM konyv';
  pool.query(query, callback);
};

// service metódus - törli az összes sort
exports.deleteBooks = (callback) => {
  const query = 'DELETE FROM konyv';
  pool.query(query, callback);
};

// --------foglalas ISBN a formhoz-----------------
exports.getISBN = (callback) => {
  const query = 'SELECT ISBN FROM konyv';
  pool.query(query, callback);
};

// ------foglalas ami checkolja, hogy a peldanyszamot ------

exports.checkPeldanySzam =  (req) => queryFunction('SELECT Peldanyszam FROM konyv WHERE ISBN=?', [req]);


exports.insertPerson = (req) => {
  const name = req;
  return queryFunction(`INSERT IGNORE INTO felhasznalo(Nev) values ("${name}");`);
};

exports.insertFoglalas = (req) => {
  const name = req.bookRName;
  const isbn = req.rentIsbn;
  return queryFunction(`INSERT IGNORE INTO kolcsonzes(KNev,KISBN) values ("${name}","${isbn}");`);
};

exports.updateKonyvSzam = (req, callback) => {
  const isbn = req;
  const query = `UPDATE konyv 
                 SET PeldanySzam = PeldanySzam - 1
                 WHERE ISBN ="${isbn}";`;
  pool.query(query, callback);
};


// ----------foglalasok getelese-----------

exports.getFoglalas = (req, callback) => {
  pool.query('SELECT * FROM kolcsonzes WHERE KISBN=?', [req], (error, kolcsonzes) => {
    if (error) {
      req.status(500).render('error', { message: `getFoglalas Select Error: ${error.message}` });
    }
    callback(kolcsonzes);
  });
};

// ----visszaszolgaltat

exports.getReturnName = (callback) => {
  const query = 'SELECT DISTINCT KNev FROM kolcsonzes';
  pool.query(query, callback);
};

exports.getReturnISBN = (callback) => {
  const query = 'SELECT DISTINCT KISBN FROM kolcsonzes';
  pool.query(query, callback);
};

exports.deleteReturn = (req, callback) => {
  const personName = req.bookRenterName;
  const isbn = req.returnISBN;

  const query = `DELETE FROM kolcsonzes
                 WHERE KISBN="${isbn}" AND KNev="${personName}";`;
  pool.query(query, callback);
};

exports.updateReturn = (req, callback) => {
  const isbn = req;
  const query = `UPDATE konyv 
                 SET PeldanySzam = PeldanySzam + 1
                 WHERE ISBN ="${isbn}";`;
  pool.query(query, callback);
};

// Authentication -- lab4


exports.insertUser = (req, callback) => {
  const { userName } = req;
  const password = req.hashWithSalt;
  const rank = req.rankOfUser;
  const query = `INSERT INTO loginfelhasznalok(Felhasznalonev,Jelszo,Jogkor) values ("${userName}","${password}","${rank}");`;
  pool.query(query, callback);
};

exports.getUser =  (req) => queryFunction('SELECT Jelszo,Jogkor FROM loginfelhasznalok WHERE Felhasznalonev=?', [req]);

// AJAX

exports.getDetails =  (req) => queryFunction('SELECT Osszefoglalo FROM konyv WHERE ISBN=?', [req]);

exports.deleteFromReservations =  (req) => queryFunction('DELETE FROM kolcsonzes WHERE KISBN=?', [req]);
exports.deleteFromBooks =  (req) => queryFunction('DELETE FROM konyv WHERE ISBN=?', [req]);
