from gevent import monkey; monkey.patch_all()
from flask import Flask, render_template
from flask_socketio import SocketIO, send, emit

# Port 5000

app = Flask(__name__)
app.debug = True
socketio = SocketIO(app)

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

@socketio.on('conect')
def handle_greetings(data):
    print("socket connected\n")
    print(data)
    send("Greetings, master")

# Running flask application from socketio.run
if __name__ == "__main__":
    socketio.run(app)
