// Connect to the server throught socket
var socket = io.connect('http://' + document.domain + ':' + location.port);

// Event handlers using socket connection 

socket.on('connect', function() {
	socket.emit('my event', {data: 'I\'m connected!'});
});

socket.on('message', function(data) {
	console.log(data);
});

socket.on('audio_chunk', function(response) {
	console.log(response);
});

socket.on('input', function(data) {
	console.log(data);
});
