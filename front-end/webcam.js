function play_video() {
  'use strict';
  var video = document.querySelector("#video")
    , canvas;

  /**
   *  generates a still frame image from the stream in the <video>
   *  appends the image to the <body>
   */
  function takeSnapshot() {
    var img = document.querySelector('img') || document.createElement('img');
    var context;
    var width = video.offsetWidth
      , height = video.offsetHeight;

    canvas = canvas || document.createElement('canvas');
    canvas.width = width;
    canvas.height = height;

    context = canvas.getContext('2d');
    context.drawImage(video, 0, 0, width, height);

    img.src = canvas.toDataURL('image/png');
    document.body.appendChild(img);
  }

  navigator.getUserMedia = navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia || navigator.msGetUserMedia || navigator.oGetUserMedia;

  if (navigator.getUserMedia) {
  	navigator.getUserMedia({video: true}, handleVideo, videoError);
  }

  function handleVideo(stream) {
  	video.src = window.URL.createObjectURL(stream);
  }

  function videoError(e) {
  	// do something
  }
  // use MediaDevices API
  // docs: https://developer.mozilla.org/en-US/docs/Web/API/MediaDevices/getUserMedia
  // if (navigator.mediaDevices) {
  //   // access the web cam
  //   navigator.mediaDevices.getUserMedia({video: true})
  //   // permission granted:
  //     .then(function(stream) {
  //       video.src = window.URL.createObjectURL(stream);
  //       video.addEventListener('click', takeSnapshot);
  //     })
  //     // permission denied:
  //     .catch(function(error) {
  //       document.body.textContent = 'Could not access the camera. Error: ' + error.name;
  //     });
  // }
}
var loadFile = function(event) {
   var output = document.getElementById('image');
   output.src = URL.createObjectURL(event.target.files[0]);
   $("#allImage").show();
   $("#video").hide();

 };
