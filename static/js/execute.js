$(document).ready(function() {
	$("form").on("submit", function(e) {
		e.preventDefault();
		window[$(this).attr("title")]();
	});
});

// Google Search

function google() {
	window.open("http://www.google.com/search?q=" + $("#googleform").val());
}

// Email Sending

function sendEmail()
{
	$('#send-button').addClass('disabled');
	var data = {
	    service_id: 'gmail',
	    template_id: 'template_5JIOuWgp',
	    user_id: 'user_ldoyQiJ5Nw76VmE3BWKhR',
	    template_params: {
	        'to_person': $('#compose-to').val(),
	        'title': $('#compose-subject').val(),
	        'content': $('#compose-message').val()
	    }
	};

	$.ajax('https://api.emailjs.com/api/v1.0/email/send', {
	    type: 'POST',
	    data: JSON.stringify(data),
	    contentType: 'application/json'
	}).done(function() {
	    alert('Your mail is sent!');
		composeTidy();
	}).fail(function(error) {
	    alert('Oops... ' + JSON.stringify(error));
		$('#send-button').removeClass('disabled');
	});
}

function composeTidy()
{
	$('#compose-to').val('');
	$('#compose-subject').val('');
	$('#compose-message').val('');
	$('#send-button').removeClass('disabled');
}

// Telling a Joke
var tellJoke = function()
{
	$.ajax('http://api.icndb.com/jokes/random/', {
		type: 'GET'
	}).done(function(data) {
		console.log(data.value.joke);
		var msg = new SpeechSynthesisUtterance(data.value.joke);
		window.speechSynthesis.speak(msg);
	}).fail(function(error) {
		var msg = new SpeechSynthesisUtterance("No Jokes for you, Corrector!");
		window.speechSynthesis.speak(msg);
	});
}

// Song
function playSong()
{
	window.open(
		"https://youtu.be/njos57IJf-0?t=1m32s",
		'_blank'
	);
}

// Dimming
function dimScreen()
{
	$("#over").addClass("overlay");
}

function brightenScreen()
{
	$("#over").removeClass("overlay");
}
