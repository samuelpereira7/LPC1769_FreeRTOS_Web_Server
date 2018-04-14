from flask import Flask, jsonify
from flask_cors import CORS
import requests

app = Flask(__name__)
CORS(app)

@app.route("/")
def hello():
    ac_const = 90/65
    r = requests.get('http://192.168.0.87:80')
    resp = str(r.content).split(',')
    a = {}
    a['x'] = int(int(resp[1]) * ac_const)
    a['y'] = int(int(resp[2]) * ac_const)
    a['z'] = int(int(resp[3]) * ac_const)
    a['t'] = resp[4]
    return jsonify(a)
if __name__ == '__main__':
    app.run(debug=True, host='localhost', port=5200, threaded=True)
