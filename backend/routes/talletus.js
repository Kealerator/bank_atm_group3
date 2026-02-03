const express = require('express');
const router = express.Router();
const talletus = require('../models/talletus_model');

router.post('/talletus/:idtili', function(request, response) {

    const idtili = request.params.idtili;
    const summa = parseFloat(request.body.summa);

    // Haetaan saldo

    talletus.haeSaldo(idtili, function(err, result) {
        if (err) {
            response.json(err.errno);
        }
        else {

            if (result.length === 0) {
                console.log("Tiliä ei löydy");
                response.json({ message: "Tiliä ei löydy" });
                return;
            }

        const saldo = parseFloat(result[0].saldo);
        const uusiSaldo = saldo + summa;


    // Päivitetään saldo
    talletus.paivitaSaldo(idtili, uusiSaldo, function(err) {
        if (err) {
            response.json(err.errno);
        } else {
            // Lisätään tilitapahtuma
            talletus.lisaaTapahtuma(idtili, +summa, function(err) {
                if (err) {
                    response.json(err.errno);
                } else {
                    // Onnistunut talletus
                    response.setHeader('Content-Type', 'application/json');
                    response.json({
                        success: true,
                        message: 'Talletus onnistui',
                        uusiSaldo: uusiSaldo
                    });
                }
            });
            }
        });
        }
    });    
});


module.exports = router;