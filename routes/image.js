var express = require('express');
var router = express.Router();
var fs = require('fs');

router.get('/app/:id', function(req, res, next) {
  switch (Number(req.params.id)) {
    case 1: // top left
      res.render('image', { imageUrl: '/images/app/egg-card.png' });
      break;
    case 2: // top right
      res.render('image', { imageUrl: '/images/app/fish-card.png' });
      break;
    case 3: // bottom left
      res.render('image', { imageUrl: '/images/app/rooster-card.png' });
      break;
    case 4: // bottom right
      res.render('image', { imageUrl: '/images/app/grass-card.png' });
      break;
    default:
      res.render('image', { });
  }
});


router.get('/download/:id', function(req, res, next) {
    res.render('amoo-norooz', { imageId: req.params.id });
});

module.exports = router;
