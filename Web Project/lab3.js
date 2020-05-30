const express = require('express'),
  fs = require('fs'),
  path = require('path'),
  eformidable = require('express-formidable');

const isbnValidator = require('isbn-validate');


const app = express();
const uploadDir = path.join(__dirname, 'uploadDir');

if (!fs.existsSync(uploadDir)) {
  fs.mkdirSync(uploadDir);
}

app.use(express.static(path.join(__dirname, 'static')));

app.use(eformidable({ uploadDir }));

const listOfBooks = [];
const bookRenters = [];

function checkValidISBN(isbNum) {
  return isbnValidator.Validate(isbNum);
}

function checkFieldValidity(objBook) {
  if (checkValidISBN(objBook.isbnNumber) === false) {
    return 'ERROR:Wrong ISBN Number';
  }

  if (objBook.bookTitle === '') {
    return 'ERROR:Empty Book Title field';
  }

  if ((objBook.bookAuthor === '') ||  (objBook.authorName.match(/[A-Z][a-z]+ [A-Z][a-z]+/) === null)) {
    return 'ERROR:Wrong Author Name';
  }

  if (objBook.bookDescription === '') {
    return 'ERROR:Empty Description field';
  }

  if (objBook.fileName === '') {
    return 'ERROR:Empty File field';
  }

  if (Number.isInteger(objBook.bookNumber) === false) {
    return 'ERROR:Booknumber is not a number';
  }

  return true;
}

function getBook(isbnNumber) {
  let i = 0;
  for (i; i < listOfBooks.length; i += 1) {
    if (listOfBooks[i][0] === isbnNumber) {
      break;
    }
  }
  if (i < listOfBooks.length) {
    if (listOfBooks[i][6] > 0) {
      listOfBooks[i][6] -= 1;
      return 1;
    }
    return 2;
  }
  return 3;
}

function rentedBefore(isbnNumber, pName) {
  let i = 0;
  for (i; i < bookRenters.length; i += 1) {
    if ((bookRenters[i][1] === isbnNumber) && (bookRenters[i][0] === pName)) {
      return i;
    }
  }

  return -1;
}

function returnBook(isbnNumber, pName, rentedIndex) {
  console.log(isbnNumber, pName, rentedIndex);
  bookRenters.splice(rentedIndex, 1);

  let i = 0;
  for (i; i < listOfBooks.length; i += 1) {
    if (listOfBooks[i][0] === isbnNumber) {
      break;
    }
  }

  listOfBooks[i][6] += 1;
}

app.post('/upload_file', (request, response) => {
  const fileHandler = request.files.myfile;

  const isbnNumber = String(request.fields.isbnNumber);
  const bookTitle = String(request.fields.bookTitle);
  const bookAuthor = String(request.fields.bookAuthor);
  const bookDescription = String(request.fields.bookDescription);
  const bookNumber = parseInt(request.fields.bookNumber, 10);
  const adminPassword = String(request.fields.adminPassword);
  const fileName = fileHandler.name;

  const objectBook = {
    isbnNumber, bookTitle, bookAuthor, bookDescription, fileName, bookNumber, adminPassword,
  };
  let returnMess = checkFieldValidity(objectBook);

  if (adminPassword === '') {
    returnMess = 'Wrong Admin Password';
  }

  if (returnMess === true) {
    listOfBooks.push([isbnNumber, bookTitle, bookAuthor, bookDescription,
      fileHandler.name, fileHandler.path, bookNumber]);

    const respBody = `<p>Succesfull Upload</p>
    <p>ISBN Number: ${isbnNumber}</p>
    <p>Book Title: ${bookTitle}</p>
    <p>Book Author: ${bookAuthor}</p>
    <p>Book Description: ${bookDescription}</p>
    <p>File: ${fileHandler.name}</p>
    <p>File's Path: ${fileHandler.path}</p>
    <p>Book Number: ${bookNumber}</p>
    <p>Admin Password: ${adminPassword}</p>
    `;

    console.log(respBody);
    response.status(200).send(respBody);
  } else {
    console.log(returnMess);
    response.status(400).send(returnMess);
  }
});

app.post('/get_book', (request, response) => {
  const personName = String(request.fields.personName);
  const isbnNumber = String(request.fields.isbnNum);
  console.log(personName, isbnNumber);

  if ((personName === '') ||  (personName.match(/[A-Z][a-z]+ [A-Z][a-z]+/) === null) || (checkValidISBN(isbnNumber) === false)) {
    const respBody = 'Wrong input parameters';
    console.log(respBody);
    response.status(200).send(respBody);
  } else {
    const succseffulRent = getBook(isbnNumber);
    if (succseffulRent === 1) {
      const dateOfRent = new Date();
      bookRenters.push([personName, isbnNumber, dateOfRent]);
      const respBody = `<p>Succesfull rent</p>
      <p>Person Name: ${personName}</p>
      <p>ISBN Number: ${isbnNumber}</p>
      <p>Date: ${dateOfRent}</p>
      `;
      console.log(respBody);
      response.status(200).send(respBody);
    } else if (succseffulRent === 2) {
      const respBody = 'Currently the book is not available';
      console.log(respBody);
      response.status(404).send(respBody);
    } else if (succseffulRent === 3) {
      const respBody = 'The typed book does not exists';
      console.log(respBody);
      response.status(404).send(respBody);
    }
  }
});

app.post('/return_book', (request, response) => {
  const personName = String(request.fields.pName);
  const isbnNumber = String(request.fields.isbnN);
  console.log(personName, isbnNumber);

  if ((personName === '') ||  (personName.match(/[A-Z][a-z]+ [A-Z][a-z]+/) === null) || !(checkValidISBN(isbnNumber))) {
    const respBody = 'Wrong input parameters';
    console.log(respBody);
    response.status(400).send(respBody);
  } else {
    const wasRented = rentedBefore(isbnNumber, personName);

    if (wasRented === -1) {
      const respBody = 'The specific book was not rented by the user';
      console.log(respBody);
      response.status(400).send(respBody);
    } else {
      returnBook(isbnNumber, personName, wasRented);
      const respBody = 'The book was succesfully returned back!';
      console.log(respBody);
      response.status(200).send(respBody);
    }
  }
});

app.listen(8080, () => {
  console.log('Server listening...');
});
