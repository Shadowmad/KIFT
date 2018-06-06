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

var dimScreen = function()
{
	document.getElementById("overlay").style.display = "block";
}

var BrightenScreen = function()
{
	document.getElementById("overlay").style.display = "none";
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
	else if (command.indexOf("PLAY A SONG") != -1)
	{
		interConnection.send("kws");
		window.location.href = "https://youtu.be/njos57IJf-0?t=1m40s";
	}
	else if (command.indexOf("DIM SCREEN") != -1)
	{
		interConnection.send("kws");
		dimScreen();
	}
	else if (command.indexOf("BRIGHTEN SCREEN") != -1)
	{
		interConnection.send("kws");
		BrightenScreen();
	}
	else
		console.log(command);
}
