const express = require('express');
const router = express.Router();
const kortti = require('../models/kortti_model');

router.get('/',
    function (request, response) {
        kortti.getAll(function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                console.log(dbResult);
                response.json(dbResult);
            }
        })
    });

router.get('/:tunnistekoodi',
    function (request, response) {
        kortti.getOne(request.params.tunnistekoodi, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult);
            }
        })
    });


router.post('/', 
function(request, response) {
  kortti.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.delete('/:tunnistekoodi', 
function(request, response) {
  kortti.delete(request.params.tunnistekoodi, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:tunnistekoodi', 
function(request, response) {
  kortti.update(request.params.tunnistekoodi, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;