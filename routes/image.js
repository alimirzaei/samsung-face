var express = require('express');
var router = express.Router();
var fs = require('fs');

router.get('/app/:id', function(req, res, next) {
  switch (Number(req.params.id)) {
    case 1:
      res.render('image', { imageUrl: '/images/cards/1.gif' ,
                            pageTopMessage: 'می تونی این کارت تبریک رو دانلود کنی یا برای کسایی که دوستشون داری تو تلگرام بفرستی. حتی می تونی برگردی و یه کارت دیگه انتخاب کنی.' ,
                            retry: 'button2-200.png',
                            telegramMessage: 'یه کارت تبریک قشنگ فرستادم.برای دیدنش روی لینک بالا کلیک کن و کارت تبریک خودت رو بساز.'});
      break;
    case 2:
      res.render('image', { imageUrl: '/images/cards/2.gif' ,
                            pageTopMessage: 'می تونی این کارت تبریک رو دانلود کنی یا برای کسایی که دوستشون داری تو تلگرام بفرستی. حتی می تونی برگردی و یه کارت دیگه انتخاب کنی.' ,
                            retry: 'button2-200.png',
                            telegramMessage: 'یه کارت تبریک قشنگ فرستادم.برای دیدنش روی لینک بالا کلیک کن و کارت تبریک خودت رو بساز.'});
      break;
    case 3:
      res.render('image', { imageUrl: '/images/cards/3.gif' ,
                            pageTopMessage: 'می تونی این کارت تبریک رو دانلود کنی یا برای کسایی که دوستشون داری تو تلگرام بفرستی. حتی می تونی برگردی و یه کارت دیگه انتخاب کنی.' ,
                            retry: 'button2-200.png',
                            telegramMessage: 'یه کارت تبریک قشنگ فرستادم.برای دیدنش روی لینک بالا کلیک کن و کارت تبریک خودت رو بساز.'});
      break;
    case 4:
      res.render('image', { imageUrl: '/images/cards/4.gif' ,
                            pageTopMessage: 'می تونی این کارت تبریک رو دانلود کنی یا برای کسایی که دوستشون داری تو تلگرام بفرستی. حتی می تونی برگردی و یه کارت دیگه انتخاب کنی.' ,
                            retry: 'button2-200.png',
                            telegramMessage: 'یه کارت تبریک قشنگ فرستادم.برای دیدنش روی لینک بالا کلیک کن و کارت تبریک خودت رو بساز.'});
      break;
    case 5:
      res.render('image', { imageUrl: '/images/cards/5.gif' ,
                            pageTopMessage: 'می تونی این کارت تبریک رو دانلود کنی یا برای کسایی که دوستشون داری تو تلگرام بفرستی. حتی می تونی برگردی و یه کارت دیگه انتخاب کنی.' ,
                            retry: 'button2-200.png',
                            telegramMessage: 'یه کارت تبریک قشنگ فرستادم.برای دیدنش روی لینک بالا کلیک کن و کارت تبریک خودت رو بساز.'});
      break;
    case 6:
      res.render('image', { imageUrl: '/images/cards/6.gif',
                            pageTopMessage: 'می تونی این مطلب رو دانلود کنی یا برای کسایی که دوستشون داری تو تلگرام بفرستی. حتی می تونی برگردی و مطالب دیگه رو انتخاب کنی.' ,
                            retry: 'button2-200.png',
                            telegramMessage: 'چند پیشنهاد خوب برای استفاده بهتر از گوشی.برای دیدنش روی لینک بالا کلیک کن و با دوستات به اشتراک بذار.'});
      break;
    case 7:
      res.render('image', { imageUrl: '/images/cards/7.gif',
                            pageTopMessage: 'می تونی این مطلب رو دانلود کنی یا برای کسایی که دوستشون داری تو تلگرام بفرستی. حتی می تونی برگردی و مطالب دیگه رو انتخاب کنی.' ,
                            retry: 'button2-200.png',
                            telegramMessage: 'چند پیشنهاد خوب برای استفاده بهتر از گوشی.برای دیدنش روی لینک بالا کلیک کن و با دوستات به اشتراک بذار.'});
      break;
    case 8:
      res.render('image', { imageUrl: '/images/cards/8.gif',
                            pageTopMessage: 'می تونی این مطلب رو دانلود کنی یا برای کسایی که دوستشون داری تو تلگرام بفرستی. حتی می تونی برگردی و مطالب دیگه رو انتخاب کنی.' ,
                            retry: 'button2-200.png',
                            telegramMessage: 'چند پیشنهاد خوب برای استفاده بهتر از گوشی.برای دیدنش روی لینک بالا کلیک کن و با دوستات به اشتراک بذار.'});
      break;
    case 9:
      res.render('image', { imageUrl: '/images/cards/9.gif',
                            pageTopMessage: 'می تونی این مطلب رو دانلود کنی یا برای کسایی که دوستشون داری تو تلگرام بفرستی. حتی می تونی برگردی و مطالب دیگه رو انتخاب کنی.' ,
                            retry: 'button2-200.png',
                            telegramMessage: 'چند پیشنهاد خوب برای استفاده بهتر از گوشی.برای دیدنش روی لینک بالا کلیک کن و با دوستات به اشتراک بذار.'});
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
