const express = require('express');
const router = express.Router();
const kortti = require('../models/kortti_model');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');

router.post('/', function(request, response){
    if(request.body.tunnistekoodi && request.body.pin){
        const tunnistekoodi=request.body.tunnistekoodi;
        const pin=request.body.pin;
        kortti.getPin(tunnistekoodi, function(err, result){
            if(err){
                response.json(err.errno);
            }
            else {
                if(result.length > 0){
                    console.log(pin);
                    bcrypt.compare(pin, result[0].pin, function(err, compareResult){
                        const token=generateAccessToken(tunnistekoodi);
                        if(compareResult){
                            response.setHeader('Content-Type', 'application/json'); 
                            response.json({
                                success: true,
                                message: "Login OK",
                                tunnistekoodi: tunnistekoodi,
                                token: token
                            });
                        }
                        else {
                            console.log("Väärä salasana");
                            response.json({"message":"tunnus ja salasana eivät täsmää"});       
                        }

                    })
                }
                else {
                    console.log("Tunnusta ei ole");
                    response.json({"message":"tunnus ja salasana eivät täsmää"});                 
                }
            }
        })
    }
    else {
        console.log("Tunnus tai salasana puuttuu");
        response.json({"message":"tunnus ja salasana eivät täsmää"});
    }
});

function generateAccessToken(tunnistekoodi) {
  return jwt.sign({ tunnistekoodi }, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports=router;