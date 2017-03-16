var express = require('express');
var router = express.Router();
var mysql      = require('mysql');
var useragent = require('useragent');
var connection = mysql.createConnection({
  host     : 'localhost',
  user     : 'root',
  password : 'P@ss4Mysql@S@msung',
  database : 'samsung'
});
 
/* GET home page. */
router.get('/', function(req, res, next) {
  var ip = req.headers['x-forwarded-for'] || 
           req.connection.remoteAddress || 
           req.socket.remoteAddress ||
           req.connection.socket.remoteAddress;
  console.warn(ip);
  var agent = useragent.parse(req.headers['user-agent']);
  connection.connect();
  var query = connection.query('INSERT INTO request_info SET ?', {ip: ip, user_agent: agent}, function (error, results, fields) {
    if (error) throw error;
    connection.end();
  });
  

  res.render('index', { title: 'Express' });
});

module.exports = router;
