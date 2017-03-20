var express = require('express');
var router = express.Router();
var ffi = require('ffi');
var multer  = require('multer');
var upload = multer({ dest: './public/images/uploads',
                      fileFilter: function (req, file, cb) {
                        if (file.mimetype !== 'image/jpeg' && file.originalname !== 'blob' && file.fieldname !== 'image') {
                          return cb(new Error('Only image files are allowed!') ,false);
                        }
                        cb(null, true);
                      },
                      limits: { fileSize: 1 * 1000 * 1000 }
                    });

var RateLimit = require('ratelimit.js').RateLimit;
var ExpressMiddleware = require('ratelimit.js').ExpressMiddleware;
var redis = require('redis');

var rateLimiter = new RateLimit(redis.createClient(), [{interval: 1, limit: 55}]);

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
router.post('/', upload.single('image'), limitEndpoint, function(req, res, next) {
  processImage.amooNowroozMaker(req.file.path, './public/images/processed/' + req.file.filename + '.jpg');
  res.json({id: req.file.filename});
});

router.get('/:id', function(req, res, next) {
  res.render('image', { imageUrl: '/images/processed/' + req.params.id + '.jpg',
                        message: 'تاری عکس، نور بد، فاصله زیاد یا دلایل دیگه ممکن است باعث عدم تشخیص چهره شود، در صورت بروز مجدد تلاش کنین.',
                        pageTopMessage: 'می تونی کارت تبریکت رو دانلود کنی یا برای کسایی که دوستشون داری تو تلگرام بفرستی. اگه کارت تبریکت رو دوست نداشتی می تونی برگردی و دوباره امتحان کنی.',
                        retry: 'button1-200.png',
                        telegramMessage: 'یه کارت تبریک قشنگ فرستادم.برای دیدنش روی لینک بالا کلیک کن و کارت تبریک خودت رو بساز.'});
});


module.exports = router;
