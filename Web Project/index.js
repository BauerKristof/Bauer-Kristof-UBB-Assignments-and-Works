const express = require('express'),
  path = require('path'),
  morgan = require('morgan'),
  helpers = require('handlebars-helpers'),
  ehandlebars = require('express-handlebars'),
  fs = require('fs'),
  errorMiddleware = require('./middleware/error'),
  requestRoutes = require('./routes/routers');


const app = express();
const uploadDir = path.join(__dirname, 'uploadDir');

if (!fs.existsSync(uploadDir)) {
  fs.mkdirSync(uploadDir);
}

// beállítjuk a handlebars-t, mint sablonmotor
app.set('view engine', 'hbs');
app.set('views', path.join(__dirname, 'views'));

app.engine('hbs', ehandlebars({
  extname: 'hbs',
  defaultView: 'main',
  layoutsDir: path.join(__dirname, 'views/layouts'),
  partialsDir: path.join(__dirname, 'views/partials'),
  helpers: helpers(),
}));


// statikus állományok (pl. CSS/kliensoldali JS)
app.use(express.static(path.join(__dirname, 'static')));

// app.use(eformidable({ uploadDir }));
app.use('/', requestRoutes);


// naplózás (globális)
app.use(morgan('tiny'));
app.use(errorMiddleware);
app.listen(8080, () => { console.log('Server listening on http://localhost:8080/ ...'); });
