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
	switch (command) {
		case command.indexOf("SET AN ALARM"):
			interConnection.send("kws");
			window.location.href = "http://localhost:" + location.port + "/alarm.html";
			break;
		case command.indexOf("SEARCH GOOGLE"):
			interConnection.send("kws");
			window.location.href = "http://google.com";
			break;
		case command.indexOf("TELL A JOKE"):
			tellJoke();
			interConnection.send("kws");
			break;
		case command.indexOf("PLAY A SONG"):
			interConnection.send("kws");
			window.location.href = "https://youtu.be/njos57IJf-0?t=1m40s";
			break;
		case command.indexOf("DIM SCREEN"):
			interConnection.send("kws");
			dimScreen();
			break;
		case command.indexOf("BRIGHTEN SCREEN"):
			interConnection.send("kws");
			BrightenScreen();
			break;
		default:
			console.log(command);
	}
}
