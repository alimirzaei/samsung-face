var express = require('express');
var router = express.Router();
var ffi = require('ffi');

var processImage = ffi.Library('./build/libface', {
  'amooNowroozMaker': [ 'void', [ 'string', 'string' ] ]
});

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

router.get('/processImage', function(req, res, next) {
  // libface.so should be in the same directory for the sake of same path
  processImage.amooNowroozMaker('/home/reza/Downloads/1.png', '/home/reza/samsung-face/public/images/1.png');
  // return JSON object that includes url of saved amooNowrooz image and related og-tag links
  res.render('image', { imageUrl: '/images/1.png' });
  // res.render('index', { url: 'Express' });
});

module.exports = router;
