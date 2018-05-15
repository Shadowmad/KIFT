from flask import Flask, render_template

# Port 5000

app = Flask(__name__)

@app.route('/')
def homepage():
    title = "Welcome to the audio controller"  
    return render_template("index.html", title=title)

if __name__ == "__main__":
    app.run(debug=True)
