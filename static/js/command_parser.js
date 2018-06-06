var parseCommand = function(command)
{
	switch (command) {
		case "SET AN ALARM":
			interConnection.send("kws");
			$("#setAlarm").toggleClass("datahid");
			$("#setAlarm").toggleClass("dataShow");
			$(".lds-hourglass").toggleClass("dataShow");
			$(".lds-ripple").toggleClass("datahid");
			break;
		case "SEARCH GOOGLE":
			interConnection.send("kws");
			$("#google").toggleClass("datahid");
			$("#google").toggleClass("dataShow");
			$(".lds-hourglass").toggleClass("dataShow");
			$(".lds-ripple").toggleClass("datahid");
			break;
		case "SEND EMAIL":
			interConnection.send("kws");
			$("#sendEmail").toggleClass("datahid");
			$("#sendEmail").toggleClass("dataShow");
			$(".lds-hourglass").toggleClass("dataShow");
			$(".lds-ripple").toggleClass("datahid");
			break;
		case "TELL A JOKE":
			tellJoke();
			interConnection.send("kws");
			$(".lds-hourglass").toggleClass("dataShow");
			$(".lds-ripple").toggleClass("datahid");
			break;
		case "PLAY A SONG":
			interConnection.send("kws");
			$(".lds-hourglass").toggleClass("dataShow");
			$(".lds-ripple").toggleClass("datahid");
			break;
		case "DIM SCREEN":
			interConnection.send("kws");
			dimScreen();
			$(".lds-hourglass").toggleClass("dataShow");
			$(".lds-ripple").toggleClass("datahid");
			break;
		case "BRIGHTEN SCREEN":
			interConnection.send("kws");
			BrightenScreen();
			$(".lds-hourglass").toggleClass("dataShow");
			$(".lds-ripple").toggleClass("datahid");
			break;
		default:
			console.log(command);
	}
}
