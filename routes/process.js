var express = require('express');
var router = express.Router();
var ffi = require('ffi');
var multer  = require('multer');
var upload = multer({ dest: './public/images/uploads' });

var RateLimit = require('ratelimit.js').RateLimit;
var ExpressMiddleware = require('ratelimit.js').ExpressMiddleware;
var redis = require('redis');

var rateLimiter = new RateLimit(redis.createClient(), [{interval: 1, limit: 8}]);

var options = {
  ignoreRedisErrors: true // defaults to false
};
var limitMiddleware = new ExpressMiddleware(rateLimiter, options);
var limitEndpoint = limitMiddleware.middleware(function(req, res, next) {
  // res.status(429).json({message: 'rate limit exceeded'});
  res.render('busy', {});
});

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

router.get('/', upload.single('image'), limitEndpoint, function(req, res, next) {
  processImage.amooNowroozMaker('./public/images/uploads/' +  'd26f08d255012f051582567086adc509' ,'./public/images/processed/' + 'd26f08d255012f051582567086adc509' + '.jpg');
  res.render('image', { imageUrl: '/images/processed/' + 'd26f08d255012f051582567086adc509' + '.jpg'});
});

module.exports = router;
