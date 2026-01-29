const db = require('../database');

const nosto = {
    haeSaldo: function(idtili, callback) {
        return db.query('select saldo from tili where idtili=?', [idtili], callback);
    },

    paivitaSaldo: function(uusiSaldo, idtili, callback) {
        return db.query('update tili set saldo=? where idtili=?', [idtili, uusiSaldo], callback);
    },

    lisaaTapahtuma: function(idtili, summa, callback) {
        return db.query('INSERT INTO tilitapahtumat (tapahtumat, summa, ajankohta, idtili) VALUES (?, ?, NOW(), ?)', ['Otto', summa, idtili], callback);
    }
};

module.exports = nosto;