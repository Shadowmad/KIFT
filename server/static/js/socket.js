// Connect to the server throught socket
var socket = io.connect('http://' + document.domain + ':' + location.port);

// Event handlers using 

socket.on('connect', function() {
	socket.emit('my event', {data: 'I\'m connected!'});
});

socket.on('message', function(data) {
	console.log(data);
})
