const db = require('../database');

const tilitapahtumat = {
  getAll: function(callback) {
    return db.query('select * from tilitapahtumat', callback);

    },
    getOne: function(id, callback) {
    return db.query('select * from tilitapahtumat where idtilitapahtumat=?', [id], callback);
 

    },
  add: function(tilitapahtumat, callback) {
    return db.query(
      'insert into tilitapahtumat (tapahtumat, summa, ajankohta, idtili) values(?,?,?,?)',
      [tilitapahtumat.tapahtumat, tilitapahtumat.summa, tilitapahtumat.ajankohta, tilitapahtumat.idtili], callback);
  

    },
  delete: function(id, callback) {
    return db.query('delete from tilitapahtumat where idtilitapahtumat=?', [id], callback);
  

    },
  update: function(id, tilitapahtumat, callback) {
    return db.query(
      'update tilitapahtumat set tapahtumat=?, summa=?, ajankohta=? where idtilitapahtumat=?',
      [tilitapahtumat.tapahtumat, tilitapahtumat.summa, tilitapahtumat.ajankohta, id], callback);
    },

    getTapahtumat: function(id, callback){
      return db.query('select tapahtumat, summa, ajankohta from tilitapahtumat where idtili = ?'+
        'order by ajankohta desc limit 10', [id], callback
       );
    }
};
module.exports = tilitapahtumat;