const express = require('express'),
  session = require('express-session'),
  validityMiddleWare = require('../middleware/checkValidity'),
  db = require('../db/db'),
  sessionmiddleware = require('../middleware/session'),
  authenticationRouter = require('./auth'),
  ajaxRouter = require('./ajaxrouter');

const router = express.Router();

router.use(session({
  secret: '142e6ecf42884f03',
  resave: false,
  saveUninitialized: true,
}));

router.use(express.urlencoded({ extended: true }));
router.use(authenticationRouter);
router.use(ajaxRouter);


router.get('/', sessionmiddleware.authorize(['felhasznalo', 'admin', 'guest']), (req, res) => {
  db.getBooks((err, konyv) => {
    if (err) {
      res.status(500).render('error', { message: `Selection unsuccessful: ${err.message}` });
    } else {
      let userInfo = '';
      if (req.session.role === 'guest') {
        userInfo = 'guest';
      } else {
        userInfo = req.session.username;
      }
      res.render('requests', { konyv, userInfo });
    }
  });
});

// konyv feltoltese
router.get('/form_kitolt', sessionmiddleware.authorize(['admin']), (req, res) => {
  let userInfo = '';
  if (req.session.role === 'guest') {
    userInfo = 'guest';
  } else {
    userInfo = req.session.username;
  }

  res.render('uploadForm', { userInfo });
});

router.post('/upload_file', validityMiddleWare.checkValidity, (req, res) => {
  db.insertBook(req.book, (error) => {
    if (error) {
      res.status(500).render('error', { message: `Insertion unsuccessful: ${error.message}` });
    } else {
      res.redirect('/');
    }
  });
});

// konyv foglalasara erkezo form
router.get('/form_lefoglal', sessionmiddleware.authorize(['felhasznalo', 'admin']), (req, res) => {
  db.getISBN((err, konyvISBN) => {
    if (err) {
      res.status(500).render('error', { message: `Selection unsuccessful: ${err.message}` });
    } else {
      // kirajzoljuk a requests sablont - a model az query eredménye
      let userInfo = '';
      if (req.session.role === 'guest') {
        userInfo = 'guest';
      } else {
        userInfo = req.session.username;
      }
      res.render('reservedList', { konyvISBN, userInfo });
    }
  });
});


// konyv foglalas checkolasa + db
router.post('/form_lefoglal/book_get', validityMiddleWare.checkReserveValidity, (req, res) => {
  let konyvSzam = 1;

  db.checkPeldanySzam(req.rentISBN)
    .then((konyv) => {
      konyvSzam = konyv[0].Peldanyszam;

      if (konyvSzam > 0) {
        return db.updateKonyvSzam(req.rentISBN);
      }
      throw new Error('Nincs konyv');
    })
    .then(() => db.insertPerson(req.bookRenterName))
    .then(() =>  {
      const bookRName = req.bookRenterName;
      const rentIsbn = req.rentISBN;
      const foglalasData = { bookRName, rentIsbn };
      db.insertFoglalas(foglalasData);
    })
    .then(() => res.redirect('/form_lefoglal'))
    .catch((err) => res.status(500).render('error', { message: `Sikertelen update ${err}` }));
});

router.get('/form_foglalas/:bookIsbn', (req, res) => {
  const ISBN = req.originalUrl.split('=');
  db.getFoglalas(ISBN[1], (kolcsonzes) => {
    let userInfo = '';
    if (req.session.role === 'guest') {
      userInfo = 'guest';
    } else {
      userInfo = req.session.username;
    }
    res.render('listReservations', { kolcsonzes, userInfo });
  });
});

router.get('/form_foglalas', (req, res) => {
  let userInfo = '';
  if (req.session.role === 'guest') {
    userInfo = 'guest';
  } else {
    userInfo = req.session.username;
  }
  res.render('getFoglalas', { userInfo });
});


// -- isbn foglalasok lekerese---
// router.post('/form_lefoglal/book_get', validityMiddleWare.checkReserveValidity, (req, res) => {

router.post('/get_foglalast', validityMiddleWare.getFoglalasok, (req, res) => {
  db.getFoglalas(req.ISBN, (kolcsonzes) => {
    res.render('listReservations', { kolcsonzes });
  });
});


// /delete-re érkezett POST esetén töröljük a tábla tartalmaát
router.post('/delete', (_req, res) => {
  db.deleteBooks((err) => {
    if (err) {
      res.status(500).render('error', { message: `Deletion unsuccessful: ${err.message}` });
    } else {
      // siker esetén visszairányítunk a lekérési oldalra
      res.redirect('index');
    }
  });
});

// konyv visszaszolgaltatas
router.get('/form_visszaszolgaltat', sessionmiddleware.authorize(['felhasznalo', 'admin']), (req, res) => {
  db.getReturnName((err, personNames) => { // getperson a konyvfoglalasokbol
    if (err) {
      res.status(500).render('error', { message: `Selection unsuccessful: ${err.message}` });
    }

    db.getReturnISBN((error, konyvISBN) => { // getperson a konyvfoglalasokbol
      if (error) {
        res.status(500).render('error', { message: `Selection unsuccessful: ${error.message}` });
      }

      let userInfo = '';
      if (req.session.role === 'guest') {
        userInfo = 'guest';
      } else {
        userInfo = req.session.username;
      }
      res.render('returnBook', { personNames, konyvISBN, userInfo });
    });
  });
});

router.post('/form_visszaszolgaltat/book_return', (req, res) => {
  validityMiddleWare.checkReturnValidty(req, res, (err) => {
    if (err) {
      res.status(500).render('error', { message: `Sikertelen beszuras ${err}` });
    } else {
      res.redirect('/');
    }
  });
});


module.exports = router;
