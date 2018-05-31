var audio = document.querySelector('audio');

var socket = new WebSocket('ws://127.0.0.1:9000', 'kift-audio-stream-protocol');

var constraints = window.constraints = {
	audio: true,
	video: false
};

// Function to catch and display and error

function handleError(error) {
	console.log('navigator.getUserMedia error: ', error);
};
var mediaObject = navigator.mediaDevices.getUserMedia(constraints)
	.then(function(stream) {
		var mediaRecorder = new MediaStreamRecorder(stream);
		mediaRecorder.recorderType = StereoAudioRecorder;
		mediaRecorder.mimeType = 'audio/pcm';
		mediaRecorder.bufferSize = 16384;
		mediaRecorder.sampleRate = 44100;
		mediaRecorder.audioChannels = 1;

		window.mr = mediaRecorder;
		mediaRecorder.ondataavailable = function(blob) {
			console.log(blob);
			socket.send(blob);
	    }
		mediaRecorder.start(1000);
	})
	.catch(handleError);
