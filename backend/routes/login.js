const express = require('express');
const router = express.Router();
const kortti = require('../models/kortti_model');
const kortti_tili = require('../models/kortti_tili_model');
const tili = require('../models/tili_model');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');

router.post('/', function (request, response) {
    if (request.body.tunnistekoodi && request.body.pin) {
        const tunnistekoodi = request.body.tunnistekoodi;
        const pin = request.body.pin;
        kortti.getPin(tunnistekoodi, function (err, result) {
            if (err) {
                response.json(err.errno);
            }
            else {
                if (result.length > 0) {
                    bcrypt.compare(pin, result[0].pin, function (err, compareResult) {
                        const token = generateAccessToken(tunnistekoodi);
                        if (compareResult) {

                            // Haetaan korttiin liitetty tili

                            // Haetaan korttiin liitetyn tilin id
                            kortti_tili.getIdByTunnistekoodi(tunnistekoodi, function (err, result) {
                                if (err) {
                                    response.json(err.errno);
                                }
                                if (!result || result.length === 0) { 
                                    return response.json({ success: false, message: "Korttiin liitettyä tiliä ei löytynyt" }); }
                                else {
                                    const idtili = result[0].idTili;

                                    // Liitetään löydetty tilin id vastaukseen
                                    response.setHeader('Content-Type', 'application/json');
                                    response.json({
                                        success: true,
                                        message: "Login OK",
                                        tunnistekoodi: tunnistekoodi,
                                        idtili: idtili,
                                        token: token
                                    });

                                }
                            });
                        }
                        else {
                            console.log("Väärä PIN");
                            response.json({ "message": "Tunnistekoodi ja PIN eivät täsmää" });
                        }

                    })
                }
                else {
                    console.log("Tunnistekoodia ei ole");
                    response.json({ "message": "Tunnistekoodi ja PIN eivät täsmää" });
                }
            }
        })
    }
    else {
        console.log("Tunnistekoodi tai PIN puuttuu");
        response.json({ "message": "Tunnistekoodi ja PIN eivät täsmää" });
    }
});

function generateAccessToken(tunnistekoodi) {
    return jwt.sign({ tunnistekoodi }, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports = router;