var parseCommand = function(command)
{
	if (command.indexOf("SET AN ALARM") != -1)
	{
		interConnection.send("kws");
		window.location.href = "http://localhost:" + location.port + "/alarm.html";
	}
	else if (command.indexOf("SEARCH GOOGLE") != -1)
	{
		interConnection.send("kws");
		window.location.href = "http://google.com";
	}
		console.log(command);
}
