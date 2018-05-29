var audio = document.querySelector('audio');

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
			mediaRecorder.pause();
			console.log(blob);
			socket.emit('audio_chunk', blob);
	    }
		socket.on('audio_resume', function(response) {
			console.log(response);
			if (response.resume)
				mediaRecorder.resume();
		});
		mediaRecorder.start(3000);
	})
	.catch(handleError);
