const express = require('express');
const router = express.Router();
const nosto = require('../models/nosto_model');

router.post('/nosto/:idtili', function(request, response) {

    const idtili = request.params.idtili;
    const summa = parseFloat(request.body.summa);

    // Haetaan saldo

    nosto.haeSaldo(idtili, function(err, result) {
        if (err) {
            response.json(err.errno);
        }
        else {

            if (result.length === 0) {
                console.log("Tiliä ei löydy");
                response.json({ message: "Tiliä ei löydy" });
                return;
            }
    // Ehtolause kymppejä varten
        if (summa % 10 !== 0) {
            console.log("Nostettava summa ei ole kymppejä");
            response.json({ message: "Nostettava summa ei ole kymppejä" });
            return;
        }

        const saldo = parseFloat(result[0].saldo);
        const luottoraja = parseFloat(result[0].luottoraja);
        const kate = saldo + luottoraja;
        
        if (summa > kate) {
            console.log("Tilillä ei ole tarpeeksi katetta");
            response.json({ message: "Tilillä ei ole tarpeeksi katetta" });
            return;
        }
    
        const uusiSaldo = saldo - summa;


    // Päivitetään saldo
    nosto.paivitaSaldo(idtili, uusiSaldo, function(err) {
        if (err) {
            response.json(err.errno);
        } else {
            // Lisätään tilitapahtuma
            nosto.lisaaTapahtuma(idtili, -summa, function(err) {
                if (err) {
                    response.json(err.errno);
                } else {
                    // Onnistunut nosto
                    response.setHeader('Content-Type', 'application/json');
                    response.json({
                        success: true,
                        message: 'Nosto onnistui',
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