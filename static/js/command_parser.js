var parseCommand = function(command)
{
	if (command.indexOf("SET AN ALARM") != -1)
	{
		window.location.href = "http://localhost:" + location.port + "/alarm.html";
		console.log('redirecting to alarm.html');
		console.log('port = ', location.port);
	}
	else
		console.log(command);
}
