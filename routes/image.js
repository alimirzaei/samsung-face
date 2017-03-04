var express = require('express');
var router = express.Router();

router.get('/', function(req, res, next) {
  res.render('image', { imageUrl: 'images/amoo.jpg' });
});

module.exports = router;
