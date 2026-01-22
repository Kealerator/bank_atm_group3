const db = require('../database');

const kortti_tili = {
  getAll: function(callback) {
    return db.query('select * from kortti_tili', callback);
  },

  getOne: function(tunnistekoodi, idtili, callback) {
    return db.query('select * from kortti_tili where tunnistekoodi=? and idtili=?', [tunnistekoodi, idtili], callback);
  },

  add: function(kortti_tili, callback) {
    return db.query(
      'insert into kortti_tili (tunnistekoodi, idtili) values(?,?)',
      [kortti_tili.tunnistekoodi, kortti_tili.idtili],
      callback
    );
  },

  delete: function(tunnistekoodi, idtili, callback) {
    return db.query('delete from kortti_tili where tunnistekoodi=? and idtili=?', [tunnistekoodi, idtili], callback);
  },

  update: function(tunnistekoodi, idtili, kortti_tili, callback) {
    return db.query(
      'update kortti_tili set tunnistekoodi=?, idtili=? where tunnistekoodi=? and idtili=?',
      [kortti_tili.tunnistekoodi, kortti_tili.idtili, tunnistekoodi, idtili],
      callback
    );
  }
};
module.exports = kortti_tili;