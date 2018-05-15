var audio = document.querySelector('audio');

var constraints = window.constraints = {
  audio: true,
  video: false
};

// Function to handle the stream from mic.
// In future send that to flask server

function handleSuccess(stream) {
  var audioTracks = stream.getAudioTracks();
  console.log('Got stream with constraints:', constraints);
  console.log('Using audio device: ' + audioTracks[0].label);
  stream.oninactive = function() {
    console.log('Stream ended');
  };
  window.stream = stream; // make variable available to browser console
  audio.srcObject = stream;
}

// Function to catch and display and error

function handleError(error) {
  console.log('navigator.getUserMedia error: ', error);
}

var mediaObject = navigator.mediaDevices.getUserMedia(constraints).
    then(handleSuccess).catch(handleError);
