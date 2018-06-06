var parseCommand = function(command)
{
	var com = false;
	switch (command) {
		case "SET AN ALARM":
		case "SET ALARM":
			interConnection.send("kws");
			$("#setAlarm").toggleClass("dataShow");
			com = true;
			break;
		case "SEARCH GOOGLE":
			interConnection.send("kws");
			$("#google").toggleClass("dataShow");
			com = true;
			break;
		case "SEND EMAIL":
		case "SEND AN EMAIL":
			interConnection.send("kws");
			$("#sendEmail").toggleClass("dataShow");
			com = true;
			break;
		case "TELL A JOKE":
			tellJoke();
			interConnection.send("kws");
			com = true;
			break;
		case "PLAY A SONG":
		case "PLAY SONG":
			interConnection.send("kws");
			playSong();
			com = true;
			break;
		case "DIM SCREEN":
			interConnection.send("kws");
			dimScreen();
			com = true;
			break;
		case "BRIGHTEN SCREEN":
			interConnection.send("kws");
			brightenScreen();
			com = true;
			break;
		case "SHUTDOWN":
			shitdown();
			break;
		default:
			console.log(command);
	}
	if (com)
	{
		$(".lds-hourglass").toggleClass("datahid");
		$(".lds-ripple").toggleClass("dataShowRipple");
	}
}
