const db = require('../database');
const bcrypt = require('bcryptjs');

const kortti = {
  getAll: function (callback) {
    return db.query('select * from kortti', callback);
  },


  getOne: function (tunnistekoodi, callback) {
    return db.query('select * from kortti where tunnistekoodi=?', [tunnistekoodi], callback);
  },


  add: function (kortti, callback) {


    bcrypt.hash(kortti.pin, 10, function(err, hashedPin) {
      return db.query(
        'insert into kortti (tunnistekoodi,pin,exp_date, idasiakas) values(?,?,?, ?)',
        [kortti.tunnistekoodi, hashedPin, kortti.exp_date, kortti.idasiakas], callback);
    });
  },


  delete: function (tunnistekoodi, callback) {
    return db.query('delete from kortti where tunnistekoodi=?', [tunnistekoodi], callback);
  },


  update: function (tunnistekoodi, kortti, callback) {

    bcrypt.hash(kortti.pin, 10, function(err, hashedPin) {
      return db.query(
        'update kortti set pin=?, exp_date=? where tunnistekoodi=?',
        [hashedPin, kortti.exp_date, tunnistekoodi], callback);
    });
  },

  getPin: function(tunnistekoodi, callback) {
    return db.query('select pin from kortti where tunnistekoodi=?', [tunnistekoodi], callback);
  }
};
module.exports = kortti;