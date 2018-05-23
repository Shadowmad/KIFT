// Connect to the server throught socket
var socket = io.connect('http://' + document.domain + ':' + location.port);
console.log(location.port);


socket.on('connect', function(message) {
	var msg = new SpeechSynthesisUtterance(message);
	window.speechSynthesis.speak(msg);
});

socket.on('message', function(data) {
	// console.log(data);
});

socket.on('audio_chunk', function(response) {
	// console.log(response);
});

socket.on('input', function(data) {
	// console.log(data);
});
