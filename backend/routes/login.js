const express = require('express');
const router = express.Router();
const kortti = require('../models/kortti_model');
const kortti_tili = require('../models/kortti_tili_model');
const tili = require('../models/tili_model');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');

router.post('/', function (request, response) {
    // Varmistetaan, että tunnistekoodi ja PIN on lähetetty pyynnössä
    if (request.body.tunnistekoodi && request.body.pin) {

        // Mikäli löytyy niin asetetaan tunnistekoodi ja pin omiksi muuttujiinsa

        const tunnistekoodi = request.body.tunnistekoodi;
        const pin = request.body.pin;

        // Ennen kuin haetaan tietokannasta tunnistekoodiin liittyvää PIN:ia, tarkistetaan onko korttiin liittyvän tunnistekoodin yritysten määrä yli 3
        kortti.getOne(tunnistekoodi, function (err, result) {
            if (err) {
                console.error("Virhe haettaessa PIN yritysten määrää:", err);
                return response.json({ success: false, message: "Virhe järjestelmässä" });
            }
            else if (!result || result.length === 0) {
                return response.json({ success: false, message: "Tunnusta ei löytynyt" });
            }
            else {
                var PINAttempts = result[0].PINAttempts || 0;
                const lastAttemptTime = result[0].LastAttempt;
                const currentTime = new Date();

                // Laske tuntien erotus viimeisimmän yrityksen ja nykyhetken välillä.
                // Määritellään muuttuja ennen haaroja, jotta sitä voi käyttää myöhemmin.
                let hoursDifference;
                if (!lastAttemptTime) {
                    hoursDifference = 168; // tai sopiva suuri arvo
                } else {
                    const timeDifference = currentTime - new Date(lastAttemptTime);
                    hoursDifference = timeDifference / (1000 * 60 * 60);
                }

                if (PINAttempts >= 3) {
                    return response.json({ success: false, message: "Kortti on lukittu liian monen väärän PIN yrityksen vuoksi. Yritä uudestaan myöhemmin." });
                }
                // Mikäli yritysten määrä on alle 3, haetaan tietokannasta tunnistekoodiin liittyvä PIN
                else {
                    kortti.getPin(tunnistekoodi, function (err, result) {
                        if (err) {
                            response.json(err.errno);
                        }
                        else {
                            // Mikäli tunnistekoodiin liittyvä PIN löytyy tietokannasta, verrataan sitä lähetettyyn PIN:iin
                            if (result.length > 0) {

                                // Verrataan lähetettyä PIN:ia tietokannasta haettuun PIN:iin bcryptin avulla
                                bcrypt.compare(pin, result[0].pin, function (err, compareResult) {
                                    const token = generateAccessToken(tunnistekoodi);

                                    // Mikäli PIN:t täsmää, haetaan korttiin liitetty tili ja palautetaan se vastauksena
                                    if (compareResult) {

                                        // Haetaan korttiin liitetyn tilin id
                                        kortti_tili.getIdByTunnistekoodi(tunnistekoodi, function (err, result) {
                                            if (err) {
                                                response.json(err.errno);
                                            }
                                            if (!result || result.length === 0) {
                                                return response.json({ success: false, message: "Korttiin liitettyä tiliä ei löytynyt" });
                                            }
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
                                    // Mikäli PIN:t eivät täsmää, tarkistetaan yritysten määrä ja päivitetään se tarvittaessa
                                    else {
                                        // Haetaan korttiin liittyvän tunnistekoodin yritysten määrä ja viimeisin yritys -aika

                                        // Mikäli viimeisin yritys on tapahtunut 168h sitten, nollataan yritysten määrä
                                        if (hoursDifference >= 168) {
                                            console.log("Viimeisin yritys tapahtui yli 168h sitten, asetetaan yritysten määrä 1:ksi");
                                            kortti.updatePinAttempts(tunnistekoodi, 1, function (err, result) {
                                                if (err) {
                                                    console.error("Virhe nollattaessa PIN yritysten määrää:", err);
                                                } else {
                                                    // Nollataan myös viimeisin yritys -aika nykyhetkeen
                                                    kortti.updateLastAttempt(tunnistekoodi, currentTime, function (err, result) {
                                                        if (err) {
                                                            console.error("Virhe päivittäessä viimeisin yritys -aikaa:", err);
                                                        } else {
                                                            response.json({ success: false, message: "PIN on väärä. Yritä uudestaan." });
                                                        }
                                                    });

                                                }
                                            });
                                        } else { // Mikäli viimeisin yritys on tapahtunut alle 168h sitten, kasvatetaan yritysten määrää yhdellä
                                            kortti.updatePinAttempts(tunnistekoodi, PINAttempts + 1, function (err, result) {
                                                if (err) {
                                                    console.error("Virhe kasvatettaessa PIN yritysten määrää:", err);
                                                } else {
                                                    kortti.updateLastAttempt(tunnistekoodi, currentTime, function (err, result) {
                                                        if (err) {
                                                            console.error("Virhe päivittäessä viimeisin yritys -aikaa:", err);
                                                        } else {
                                                            response.json({ success: false, message: "PIN on väärä. Yritä uudestaan." });
                                                        }
                                                    });
                                                }
                                            });
                                       }

                                    }
                                });

                            }
                            // Mikäli tunnistekoodiin liittyvää PIN:ia ei löydy tietokannasta, palautetaan virheilmoitus
                            else {
                                console.log("Väärä PIN");
                                response.json({ "message": "Tunnistekoodi ja PIN eivät täsmää" });
                            }

                        }
                    });
                }
            }
        });
    }
    // Mikäli tunnistekoodi tai PIN puuttuu pyynnöstä, palautetaan virheilmoitus
    else {
        console.log("Tunnistekoodi tai PIN puuttuu");
        response.json({ "message": "Tunnistekoodi ja PIN eivät täsmää" });
    }
});

function generateAccessToken(tunnistekoodi) {
    return jwt.sign({ tunnistekoodi }, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports = router;