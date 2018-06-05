var tellJoke = function()
{
	var request = new XMLHttpRequest();

	request.open('GET', 'http://api.icndb.com/jokes/random/', true);
	request.onload = function () {
		var data = JSON.parse(this.response);
		if (request.status >= 200 && request.status < 400)
		{
			console.log(data.value.joke);
			var msg = new SpeechSynthesisUtterance(data.value.joke);
			window.speechSynthesis.speak(msg);
		}
	}
	request.send();
}

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
	else if (command.indexOf("TELL A JOKE") != -1)
	{
		tellJoke();
		interConnection.send("kws");
	}
	else
		console.log(command);
}
