const db = require('../database');

const nosto = {
    haeSaldo: function(idtili, callback) {
        return db.query('select saldo, luottoraja from tili where idtili=?', [idtili], callback);
    },

    paivitaSaldo: function(idtili, uusiSaldo, callback) {
        return db.query('update tili set saldo=? where idtili=?', [uusiSaldo, idtili], callback);
    },

    lisaaTapahtuma: function(idtili, summa, callback) {
        return db.query('INSERT INTO tilitapahtumat (tapahtumat, summa, ajankohta, idtili) VALUES (?, ?, NOW(), ?)', ['Otto', summa, idtili], callback);
    }
};

module.exports = nosto;