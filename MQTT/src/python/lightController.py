import time
import paho.mqtt.client as mqtt_client
import random
from uuid import getnode as get_mac
import hashlib

broker="broker.emqx.io"

h = hashlib.new('sha256')
mac = get_mac()
h.update(str(mac).encode())
pub_id = h.hexdigest()[:10]
print(f"Listen me at id {pub_id}")

client = mqtt_client.Client(
    mqtt_client.CallbackAPIVersion.VERSION2,
    pub_id
)

print("Connecting to broker",broker)
print(client.connect(broker))
client.loop_start()
print("Publishing")

for i in range(100):
    state = "on" if random.randint(0, 1) else "off"
    print(f"Publishung {state}")
    client.publish(f"lab/{pub_id}/led/state", state)
    time.sleep(2)

client.disconnect()
client.loop_stop()