import time
import paho.mqtt.client as mqtt_client
import random
from uuid import getnode as get_mac
import hashlib
import serial
import time
import requests

h = hashlib.new('sha256')
mac = get_mac()
h.update(str(mac).encode())
pub_id = h.hexdigest()[:10]
payload = {
    "message": pub_id
}
response = requests.post("http://10.8.0.1:5000/refresh", json=payload)
if response.status_code == 200:
    print("OK")
else:
    print(f"Request failed with status code {response.status_code}")
    raise Exception("Can't publish id")


broker="broker.emqx.io"
port_photo = "/dev/ttyUSB0"
connection_photo = serial.Serial(port_photo, timeout=1) # baudrate=9600
client = mqtt_client.Client(
    mqtt_client.CallbackAPIVersion.VERSION2,
    pub_id
)

print("Connecting to broker",broker)
print(client.connect(broker))
client.loop_start()
print("Publishing")
import time
def getValues(conn):


    start_time = time.time()
    returns=[]
    print("connect")
    conn.write(b"p")
    resp = conn.readlines()
    end_time = time.time()
    elapsed_time = end_time - start_time

    print(f"The task took {elapsed_time:.2f} seconds to complete. {len(resp)}  , {resp}")


for i in range(100):
    connection_photo.write(b"p")


    resp= connection_photo.readline().decode("ASCII")
    photo_val =int(resp.replace("\n",""))// 4 #нормализация до 255
    print(f"Publishung {photo_val}")
    client.publish(f"lab/{pub_id}/photo/instant", photo_val)
    time.sleep(1)

client.disconnect()
client.loop_stop()