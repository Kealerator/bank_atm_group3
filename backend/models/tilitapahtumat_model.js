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
      return db.query('select tapahtumat, summa, date_format(ajankohta, "%d.%m.%Y, %H:%i:%s") as ajankohta from tilitapahtumat where idtili = ?'+
        'order by ajankohta desc limit 10', [id], callback
       );
    },
    
  getTilitapahtumaByTili(id, callback){
    return db.query('SELECT tili.idtili, tili.tilinumero, tilitapahtumat.tapahtumat, tilitapahtumat.summa, DATE_FORMAT(tilitapahtumat.ajankohta, "%d.%c.%Y, %H:%i:%s") as ajankohta FROM tili inner join tilitapahtumat ON tili.idtili=tilitapahtumat.idtili where tili.idtili=?'+'order by ajankohta desc',[id],callback);
  }
};
module.exports = tilitapahtumat;