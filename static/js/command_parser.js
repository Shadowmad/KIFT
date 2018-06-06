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
