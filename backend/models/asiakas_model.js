const db = require('../database');

const asiakas = {
  getAll: function(callback) {
        return db.query('select * from asiakas', callback);
  },



  getOne: function(id, callback) {
        return db.query('select * from asiakas where idasiakas=?', [id], callback);
  },


  add: function(asiakas, callback) {
        return db.query('insert into asiakas (etunimi, sukunimi, osoite, puhelinnumero) values(?,?,?,?)',
        [asiakas.etunimi, asiakas.sukunimi, asiakas.osoite, asiakas.puhelinnumero], callback);


  },
  delete: function(id, callback) {
        return db.query('delete from asiakas where idasiakas=?', [id], callback);



  },
  update: function(id, Asiakas, callback) {
    return db.query(
        'update asiakas set etunimi=?, sukunimi=?, osoite=?, puhelinnumero=? where idasiakas=?',
        [asiakas.etunimi, asiakas.sukunimi, asiakas.osoite, asiakas.puhelinnumero, id], callback);
  }
};
module.exports = asiakas;