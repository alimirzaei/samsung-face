var express = require('express');
var router = express.Router();
var fs = require('fs');

router.get('/app/:id', function(req, res, next) {
  switch (Number(req.params.id)) {
    case 1:
      res.render('image', { imageUrl: '/images/cards/1.gif' });
      break;
    case 2:
      res.render('image', { imageUrl: '/images/cards/2.gif' });
      break;
    case 3:
      res.render('image', { imageUrl: '/images/cards/3.gif' });
      break;
    case 4:
      res.render('image', { imageUrl: '/images/cards/4.gif' });
      break;
    case 5:
      res.render('image', { imageUrl: '/images/cards/5.gif' });
      break;
    case 6:
      res.render('image', { imageUrl: '/images/cards/6.gif' });
      break;
    case 7:
      res.render('image', { imageUrl: '/images/cards/7.gif' });
      break;
    case 8:
      res.render('image', { imageUrl: '/images/cards/8.gif' });
      break;
    case 9:
      res.render('image', { imageUrl: '/images/cards/9.gif' });
      break;
    default:
      res.render('image', { });
  }
});


router.get('/download/:id', function(req, res, next) {
   if (req.params.id.length > 15) {
     res.render('amoo-norooz', { imageId: req.params.id , imageFolder: 'processed', imageType: 'jpg'});
   } else {
     res.render('amoo-norooz', { imageId: req.params.id, imageFolder: 'cards', imageType: 'gif'});
   }
});

module.exports = router;
