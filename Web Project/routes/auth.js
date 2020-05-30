const express = require('express'),
  crypto = require('crypto'),
  db = require('../db/db'),
  sessionmiddleware = require('../middleware/session');


const hashSize = 32,
  saltSize = 16,
  hashAlgorithm = 'sha512',
  iterations = 1000;

const router = express.Router();

router.use(express.urlencoded({ extended: true }));

router.get('/register', sessionmiddleware.authorize(['guest']), (req, res) => {
  let userInfo = '';
  if (req.session.role === 'guest') {
    userInfo = 'guest';
  } else {
    userInfo = req.session.username;
  }
  res.render('register', { userInfo });
});


router.get('/login', (req, res) => {
  let userInfo = '';
  if (req.session.role === 'guest') {
    userInfo = 'guest';
  } else {
    userInfo = req.session.username;
  }
  res.render('login', { userInfo });
});


router.post('/check_hash', (req, res) => {
  // a konkatenált hash-t és sót adatbázisból kérnénk le
  const { userName, passWord } = req.body;
  // hexa string dekódolás és dekonkatenálás

  db.getUser(userName)
    .then((registeredUser) =>  {
      const hashWithSalt = registeredUser[0].Jelszo;
      // hexa string dekódolás és dekonkatenálás
      const expectedHash = hashWithSalt.substring(0, hashSize * 2),
        salt = Buffer.from(hashWithSalt.substring(hashSize * 2), 'hex');
      // újra-hash-elés
      const binaryHash = crypto.pbkdf2Sync(passWord, salt, iterations, hashSize, hashAlgorithm);
      // hexa stringgé alakítás
      const actualHash = binaryHash.toString('hex');

      if (expectedHash === actualHash) {
        req.session.username = userName;
        req.session.role = registeredUser[0].Jogkor;
        res.redirect('/');
      } else {
        throw new Error('Nem egyezik meg a jelszo');
      }
    })
    .catch((err) => res.status(500).render('error', { message: `Hiba ${err}` }));
});

router.post('/create_hash', (req, res) => {
  const { userName, passWord, adminPassword } = req.body;
  // só generálása
  const salt = crypto.randomBytes(saltSize);
  // hash készítése
  const hash = crypto.pbkdf2Sync(passWord, salt, iterations, hashSize, hashAlgorithm);
  // konkatenálás és hexa stringgé alakítás
  const hashWithSalt = Buffer.concat([hash, salt]).toString('hex');
  // a konkatenált hash-t és sót tárolnánk adatbázisban
  let rankOfUser = 'felhasznalo';
  if (adminPassword === 'adminpass') {
    rankOfUser = 'admin';
  }

  const messageToSend = { userName, hashWithSalt, rankOfUser };
  db.insertUser(messageToSend, (err) => {
    if (err) {
      res.status(500).render('error', { message: `Sikertelen felhasznalo beszuras ${err}` });
    } else {
      res.redirect('/login');
    }
  });
});

router.get('/logout', (req, res) => {
  req.session.destroy((err) => {
    if (err) {
      res.status(500).render('error', { message: `Session reset error: ${err.message}` });
    } else {
      res.redirect('/');
    }
  });
});

module.exports = router;
