var audio = document.querySelector('audio');

var socket = new WebSocket('ws://127.0.0.1:9000', 'kift-audio-stream-protocol');
var interConnection = new WebSocket('ws://127.0.0.1:9000', 'kift-switch-mode');

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


interConnection.onmessage = function (message) {
	console.log('interconnection = ', message);
}

socket.onmessage = function (message) {
	if (!message.data.search('minion')) {
		interConnection.send("ngram");
		$(".data").removeClass("dataShow");
		$(".lds-hourglass").toggleClass("datahid");
		$(".lds-ripple").toggleClass("dataShowRipple");
	}
	else {
		parseCommand(message.data);
	}
}
