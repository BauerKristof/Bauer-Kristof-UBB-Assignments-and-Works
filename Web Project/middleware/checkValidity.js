const eformidable = require('formidable'),
  isbnValidator = require('isbn-validate'),
  db = require('../db/db');


function checkValidISBN(isbNum) {
  return isbnValidator.Validate(isbNum);
}

function checkValidAuthor(authorName) {
  if (authorName.match(/[A-Z][a-z]+ [A-Z][a-z]+/) === null) {
    return false;
  } return true;
}

function checkFieldValidity(isbnNum, bookTitle, bookAuthor, bookDescription, fileName, bookNumber) {
  if (checkValidISBN(isbnNum) === false) {
    return 'ERROR:Wrong ISBN Number';
  }

  if (bookTitle === '') {
    return 'ERROR:Empty Book Title field';
  }

  if ((bookAuthor === '') || (checkValidAuthor(bookAuthor) === false)) {
    return 'ERROR:Wrong Author Name';
  }

  if (bookDescription === '') {
    return 'ERROR:Empty Description field';
  }

  if (fileName === '') {
    return 'ERROR:Empty File field';
  }

  if (Number.isInteger(bookNumber) === false) {
    return 'ERROR:Booknumber is not a number';
  }

  return true;
}

// loggoljunk minden kérést az adatbázisba, mint middleware
exports.checkValidity = (request, res, next) => {
  const form = eformidable({ multiples: true });

  form.parse(request, (err, fields, files) => {
    if (err) {
      // next(err);
      res.status(500).render('error', { message: 'Parse error' });
      return;
    }

    const fileHandler = files.myfile;
    const isbnNumber = String(fields.isbnNumber);
    const bookTitle = String(fields.bookTitle);
    const bookAuthor = String(fields.bookAuthor);
    const bookDescription = String(fields.bookDescription);
    const bookNumber = parseInt(fields.bookNumber, 10);
    const adminPassword = String(fields.adminPassword);
    const bookCoverPath = fileHandler.path;

    let returnMess = checkFieldValidity(isbnNumber, bookTitle, bookAuthor,
      bookDescription, fileHandler.name, bookNumber, adminPassword); // filehandler.name kell ide!

    if (adminPassword === '') {
      returnMess = 'Wrong Admin Password';
    }

    if (returnMess === true) {
      const listOfBooks = {
        isbnNumber, bookTitle, bookAuthor, bookDescription, bookCoverPath, bookNumber,
      };

      request.book = listOfBooks;
      next();
    } else {
      res.status(500).render('error', { message: 'Hibas bemeneti adatok' });
      // next('Hibas bemeneti adatok');
    }
  });
};

exports.checkReturnValidty = (request, res, next) => {
  const form = eformidable({ multiples: true });

  form.parse(request, (err, fields) => {
    if (err) {
      next(err);
      return;
    }

    const bookRenterName = fields.personName;
    const returnISBN = fields.bookIsbnNumber;
    const objectReturn = { bookRenterName, returnISBN };
    // kolcsonzesbol kitorol
    db.deleteReturn(objectReturn, (error) => {
      if (error) {
        res.status(500).render('error', { message: `Deletion unsuccessful: ${error.message}` });
        res.redirect('/form_visszaszolgaltat');
      }
    });

    db.updateReturn(returnISBN, (errorRet) => {
      if (errorRet) {
        res.status(500).render('error', { message: `Update unsuccessful: ${errorRet.message}` });
        res.redirect('/form_visszaszolgaltat');
      }
    });
  });
};

exports.checkReserveValidity = (request, res, next) => {
  const form = eformidable({ multiples: true });

  form.parse(request, (err, fields) => {
    if (err) {
      // next(err);
      // render
      return;
    }
    const bookRenterName = fields.personName;
    const rentISBN = fields.bookIsbnNumber;
    /* db.checkPeldanySzam(rentISBN,(konyv) => {
      konyv.forEach((konyv) => {
        console.log(konyv);
        konyvSzam=konyv.Peldanyszam;
        //console.log(`Előadó: ${konyv.Peldanyszam}`);
      });
    }); */
    request.rentISBN = rentISBN;
    request.bookRenterName = bookRenterName;

    next();
    /* } else {
      // next('Nincs belole peldany mar :<');
      res.status(500).render('error', { message: 'Nincs belole peldany mar :<' });
    } */
  });
};


exports.getFoglalasok = (request, res, next) => {
  const form = eformidable({ multiples: true });

  form.parse(request, (err, fields) => {
    if (err) {
      next(err);
      return;
    }
    const ISBN = fields.isbnNumber;
    request.ISBN = ISBN;
    next();
  });
};
