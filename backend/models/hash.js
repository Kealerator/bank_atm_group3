const bcrypt = require('bcryptjs');
const saltRounds = 10;

function genHash(input, callback) {
    bcrypt.genSalt(saltRounds, (err, salt) => {

        if (err) {

            // For debugging purposes
            // console.log("Error generating hash salt.");

            return callback(err, null);
        } else {
            // For debugging purposes
            // console.log("Salt generation success.");
        }

        bcrypt.hash(input, salt, (err, hash) => {
            if (err) {

                // For debugging purposes
                // console.log("Error hashing input.");

                return callback(err, null);
            } else {

                // For debugging purposes
                //console.log("Hashing successful.");

                callback(null, hash);
            }
        });
    });
}

module.exports = { genHash };
