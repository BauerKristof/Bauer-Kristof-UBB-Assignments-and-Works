const express = require('express'),
  bodyParser = require('body-parser'),
  db = require('../db/db');

const router = express.Router();

router.use(express.urlencoded({ extended: true }));
router.use(bodyParser.json());

// AJAX
router.post('/sendDetails', (req, res) => {
  const { ISBN } = req.body;

  db.getDetails(ISBN)
    .then((obj) =>  {
      res.status(200);
      res.send(JSON.stringify(obj[0].Osszefoglalo));
    })
    .catch((err) => res.status(500).render('error', { message: `Hiba ${err}` }));
});

router.post('/removeFromList', (req, res) => {
  if (req.session.role === 'admin') {
    const { ISBN } = req.body;
    console.log(ISBN);

    db.deleteFromReservations(ISBN)
      .then(() => db.deleteFromBooks(ISBN))
      .then(() => {
        res.status(200);
        res.send('Sikeres torles az adatbazisbol');
      })
      .catch((err) => {
        res.status(401);
        res.send('Hibas adatbazis muvelet');
        console.log(err);
      });
  } else {
    res.status(401);
    res.send('Sikertelen torles: Csak az adminoknak engedelyezett');
  }
});

module.exports = router;
