var express = require('express');
var router = express.Router();
var fs = require('fs');

router.get('/app/:id', function(req, res, next) {
  switch (Number(req.params.id)) {
    case 1: // top left
      res.render('image', { imageUrl: '/images/app/chat-card.jpg' });
      break;
    case 2: // top right
      res.render('image', { imageUrl: '/images/app/khros-card.jpg' });
      break;
    case 3: // bottom left
      res.render('image', { imageUrl: '/images/app/sib-card.jpg' });
      break;
    case 4: // bottom right
      res.render('image', { imageUrl: '/images/app/sabze-card.jpg' });
      break;
    default:
      res.render('image', { });
  }
});


router.get('/download/:id', function(req, res, next) {
    res.render('amoo-norooz', { imageId: req.params.id });
});

module.exports = router;
