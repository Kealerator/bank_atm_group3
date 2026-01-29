const express = require('express');
const router = express.Router();
const kortti_tili = require('../models/kortti_tili_model');

router.get('/',
    function (request, response) {
        kortti_tili.getAll(function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                console.log(dbResult);
                response.json(dbResult);
            }
        })
    });

router.get('/:tunnistekoodi/:idtili',
    function (request, response) {
        kortti_tili.getOne(request.params.tunnistekoodi, request.params.idtili, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult); 
            }
        })
    });

  router.get('/:tunnistekoodi',
    function (request, response) {
        kortti_tili.getIdByTunnistekoodi(request.params.tunnistekoodi, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult); 
            }
        })
    });


router.post('/', 
function(request, response) {
  kortti_tili.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.delete('/:tunnistekoodi/:idtili', 
function(request, response) {
  kortti_tili.delete(request.params.tunnistekoodi, request.params.idtili, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:tunnistekoodi/:idtili', 
function(request, response) {
  kortti_tili.update(request.params.tunnistekoodi, request.params.idtili, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;