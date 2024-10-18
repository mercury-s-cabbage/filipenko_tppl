from flask import Flask, request, jsonify

app = Flask(__name__)

pub_id = "1.2.3.4"

@app.route('/refresh', methods=['POST'])
def refresh():
    global pub_id
    data = request.get_json()
    pub_id = data['message']
    return "OK", 200

@app.route('/get_id', methods=['GET'])
def get_id():
    return jsonify({"pub_id": pub_id}), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
