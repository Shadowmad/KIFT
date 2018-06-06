var parseCommand = function(command)
{
	switch (command) {
		case command.indexOf("SET AN ALARM"):
			interConnection.send("kws");
			$("#setAlarm").toogleClass("datahid");
			$("#setAlarm").toogleClass("dataShow");
			break;
		case command.indexOf("SEARCH GOOGLE"):
			interConnection.send("kws");
			$("#google").toogleClass("datahid");
			$("#google").toogleClass("dataShow");
			break;
		case command.indexOf("SEND EMAIL"):
			interConnection.send("kws");
			$("#sendEmail").toogleClass("datahid");
			$("#sendEmail").toogleClass("dataShow");
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
