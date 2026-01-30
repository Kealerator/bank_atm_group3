const db = require('../database');

const tili = {
    getAll: function(callback) {
        return db.query('select * from tili', callback);
    },
   
    getOne: function(id, callback) {
        return db.query('select * from tili where idtili=?', [id], callback);
    },

    
    add: function(tili, callback) {
        return db.query(
        'insert into tili (tilinumero,saldo,idasiakas) values(?,?,?)',
        [tili.tilinumero, tili.saldo, tili.idasiakas], callback);
    },
  
  
    delete: function(id, callback) {
        return db.query('delete from tili where idtili=?', [id], callback);
    },
  
    update: function(id, tili, callback) {
        return db.query(
      'update tili set tilinumero=?, saldo=? where idtili=?',
      [tili.tilinumero, tili.saldo, id], callback);
  }
};
module.exports = tili;