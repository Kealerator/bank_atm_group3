const db = require('../database');

const kortti = {
  getAll: function(callback) {
    return db.query('select * from kortti', callback);
  },
    

    getOne: function(tunnistekoodi, callback) {
        return db.query('select * from kortti where tunnistekoodi=?', [tunnistekoodi], callback);
  },


    add: function(kortti, callback) {
        return db.query(
        'insert into kortti (tunnistekoodi,pin,exp_date, idasiakas) values(?,?,?, ?)',
        [kortti.tunnistekoodi, kortti.pin, kortti.exp_date, kortti.idasiakas], callback);
  },
  

        delete: function(tunnistekoodi, callback) {
        return db.query('delete from kortti where tunnistekoodi=?', [tunnistekoodi], callback);
  },


    update: function(tunnistekoodi, kortti, callback) {
        return db.query(
        'update kortti set pin=?, exp_date=? where tunnistekoodi=?',
        [kortti.pin, kortti.exp_date, tunnistekoodi], callback);
  }
};
module.exports = kortti;