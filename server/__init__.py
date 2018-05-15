from flask import Flask, render_template

# Port 5000

app = Flask(__name__)

@app.route('/')
def homepage():
    title = "Welcome to the audio controller"
    paragraph = ["Warning: if you're not using headphones, pressing play will cause feedback.",
                "Render the audio stream from an audio-only getUserMedia() call with an audio element.",
                "The MediaStream object stream passed to the getUserMedia() callback is in global scope, so you can inspect it from the console."]
    return render_template("index.html", title=title, paragraph=paragraph)

@app.route('/alarm')
def alarmPage():
    title = "Set the alarm"
    paragraph = ["Description of alarm :)"]
    return render_template("alarm.html", title=title, paragraph=paragraph)

if __name__ == "__main__":
    app.run(debug=True)
