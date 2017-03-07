var express = require('express');
var router = express.Router();
var ffi = require('ffi');
var multer  = require('multer');
var upload = multer({ dest: '/home/reza/samsung-face/public/images/uploads' });

var processImage = ffi.Library('./build/libface', {
  'amooNowroozMaker': [ 'void', [ 'string', 'string' ] ]
});

/* GET image page with processedImage */
router.post('/', upload.single('image'), function(req, res, next) {
  processImage.amooNowroozMaker(req.file.path, '/home/reza/samsung-face/public/images/processed/' + req.file.filename + '.png');
  res.render('image', { imageUrl: '/images/processed/' + req.file.filename + '.png'});
});

module.exports = router;
