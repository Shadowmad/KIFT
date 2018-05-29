from gevent import monkey; monkey.patch_all()
from flask import Flask, render_template
from flask_socketio import SocketIO, send, emit
import shlex
from subprocess import Popen, PIPE

# Port 5000

app = Flask(__name__)
app.debug = True
socketio = SocketIO(app)

def get_exitcode_stdout_stderr(cmd):
    """
    Execute the external command and get its exitcode, stdout and stderr.
    """
    args = shlex.split(cmd)

    proc = Popen(args, stdout=PIPE, stderr=PIPE)
    out, err = proc.communicate()
    exitcode = proc.returncode
    #
    return exitcode, out, err

@app.route('/')
def homepage():
    title = "Welcome to the audio controller"
    paragraph = ["Warning: if you're not using headphones, pressing play will cause feedback.",
                "Render the audio stream from an audio-only getUserMedia() call with an audio element.",
                "The MediaStream object stream passed to the getUserMedia() callback is in global scope, so you can inspect it from the console."]
    return render_template("index.html", title=title, paragraph=paragraph)

# Functions to deal with socket inputs / outputs
@socketio.on('message')
def handle_message(message):
    print('received message: ' + message)
    send(message)

@socketio.on('connect')
def handle_greetings():
    print("socket connected\n")
    emit('connect', "Greetings, master")

@socketio.on('audio_chunk')
def handle_voice_input(input_buffer):
	myfile = "./myfile.raw"
	with open(myfile, 'ab') as f:
		f.write(input_buffer)
	cmd = "pocketsphinx_continuous -infile myfile.raw"
	exitcode, out, err = get_exitcode_stdout_stderr(cmd)
	emit('audio_chunk', out)
	emit('audio_resume', {'resume': "true"})

# Running flask application from socketio.run
@app.route('/alarm')
def alarmPage():
    title = "Set the alarm"
    paragraph = ["Description of alarm :)"]
    return render_template("alarm.html", title=title, paragraph=paragraph)

if __name__ == "__main__":
    socketio.run(app)
