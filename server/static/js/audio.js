var audio = document.querySelector('audio');

var constraints = window.constraints = {
	audio: true,
	video: false
};

// Function to handle the stream from mic.
// In future send that to flask server

// function handleSuccess(stream) {
// 	console.log(stream);
// 	var audioTracks = stream.getAudioTracks();
// 	console.log('Got stream with constraints:', constraints);
// 	console.log('Using audio device: ' + audioTracks[0].label);
// 	stream.oninactive = function() {
// 		console.log('Stream ended');
// 	};
// 	window.stream = stream; // make variable available to browser console
// 	audio.srcObject = stream;
// }

function convertFloat32ToInt16(buffer) {
  l = buffer.length;
  buf = new Int16Array(l);
  while (l--) {
    buf[l] = Math.min(1, buffer[l])*0x7FFF;
  }
  return buf.buffer;
}



function handleSuccess(stream) {
	console.log(stream)
	var context = new AudioContext();
	var source = context.createMediaStreamSource(stream);
	var processor = context.createScriptProcessor(16384, 1, 1);

	source.connect(processor);
	processor.connect(context.destination);
	processor.onaudioprocess = function(e) {
		console.log(e.inputBuffer);

		// In order to get int16 representation use following:
		// let dataBlock = convertFloat32ToInt16(e.inputBuffer.getChannelData(0));
		let dataBlock = e.inputBuffer.getChannelData(0);
		console.log(dataBlock)

		socket.emit('audio_chunk', dataBlock);
		context.resume().then( () => {
			console.log('Playback resumed successfuly');
		});
	};
};

// Function to catch and display and error

function handleError(error) {
	console.log('navigator.getUserMedia error: ', error);
};

var mediaObject = navigator.mediaDevices.getUserMedia(constraints).
	then(handleSuccess).catch(handleError);
