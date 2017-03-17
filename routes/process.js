var express = require('express');
var router = express.Router();
var ffi = require('ffi');
var multer  = require('multer');
var upload = multer({ dest: './public/images/uploads' });

var processImage = ffi.Library('./build/libface', {
  'amooNowroozMaker': [ 'void', [ 'string', 'string' ] ],
  'init':['void', []]
});

processImage.init();

/* GET image page with processedImage */
router.post('/', upload.single('image'), function(req, res, next) {
  console.warn(req.file.path);
  processImage.amooNowroozMaker(req.file.path, './public/images/processed/' + req.file.filename + '.jpg');
  res.json({id: req.file.filename});
});

router.get('/:id', upload.single('image'), function(req, res, next) {
  res.render('image', { imageUrl: '/images/processed/' + req.params.id + '.jpg'});
});

router.get('/', upload.single('image'), function(req, res, next) { 
  processImage.amooNowroozMaker('./public/images/uploads/' +  'd26f08d255012f051582567086adc509' ,'./public/images/processed/' + 'd26f08d255012f051582567086adc509' + '.jpg');
  res.render('image', { imageUrl: '/images/processed/' + 'd26f08d255012f051582567086adc509' + '.jpg'});
});

module.exports = router;
