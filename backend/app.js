var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const jwt = require('jsonwebtoken');

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');


const asiakasRouter = require('./routes/asiakas');
const korttiRouter = require('./routes/kortti');
const tiliRouter = require('./routes/tili');
const tilitapahtumatRouter = require('./routes/tilitapahtumat');
const kortti_tiliRouter = require('./routes/kortti_tili');
const loginRouter = require('./routes/login');
const nostoRouter = require('./routes/nosto');
const talletusRouter = require('./routes/talletus');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));



app.use('/', indexRouter);
app.use('/login', loginRouter);


// Suojatut
app.use(authenticateToken);
app.use('/asiakas', asiakasRouter);
app.use('/kortti', korttiRouter);
app.use('/tili', tiliRouter);
app.use('/tilitapahtumat', tilitapahtumatRouter);
app.use('/kortti_tili', kortti_tiliRouter);
app.use('/', nostoRouter);
app.use('/', talletusRouter);




function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization'];
    // Extract token by removing "Bearer " prefix from "Bearer "
    const token = authHeader && authHeader.split(' ')[1];

    if (token == null) return res.sendStatus(401);
    jwt.verify(token, process.env.MY_TOKEN, function(err, user) {
      if (err) {
        return res.sendStatus(403);
      }
      req.user = user;
      next();
    })
  }

module.exports = app;
