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
        'insert into tili (tilinumero,saldo,luottoraja,idasiakas) values(?,?,?,?)',
        [tili.tilinumero, tili.saldo,tili.luottoraja, tili.idasiakas], callback);
    },
  
  
    delete: function(id, callback) {
        return db.query('delete from tili where idtili=?', [id], callback);
    },
  
    update: function(id, tili, callback) {
        return db.query(
      'update tili set tilinumero=?, saldo=?, luottoraja=? where idtili=?',
      [tili.tilinumero, tili.saldo, tili.luottoraja, id], callback);
  },

  getSaldo: function(id, callback){
    return db.query('select asiakas.etunimi, asiakas.sukunimi, tili.saldo from tili '+
    'join asiakas on tili.idasiakas = asiakas.idasiakas where tili.idtili = ?', [id], callback
    //Hakee nyt idtili mukaan saldon.
    //Vaihtaa voi esim tilinumeron mukaan
    );
  }

};
module.exports = tili;