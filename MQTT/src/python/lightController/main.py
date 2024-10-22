import serial
import time
responses = {'d': 7,  # "led_off"
             'u': 6,  # "led_on"
             'p': 4}  # 0 -> 1023 zero fill to leftside
port_led = "/dev/ttyUSB0" # "COM4" or similar for windows
port_photo =  "/dev/ttyUSB0" # "COM4" or similar for windows
#connection_led = serial.Serial(port_led, timeout=1) # baudrate=9600
connection_photo = serial.Serial(port_photo, timeout=1,baudrate=1000000) # baudrate=9600
count=0
buf = 0
c= 'p'.encode()
time.sleep(6)
start_time = time.time()
def send_command(cmd: str, response_len: int, connection: serial.Serial) -> str:
    global count
    global start_time
    global buf
    global c

    connection.write(c)
    if response_len > 0:
        # connection.in_waiting <-> available()
        resp = connection.read()
    if count%1000==0:

        end_time = time.time()
        elapsed_time = end_time - start_time
        print(f"The task took {elapsed_time:.2f} seconds to complete {count} values, last 1000 values in {round(end_time-buf,3)}")
        buf = end_time
    count+=1
    return resp

while True:
    photo_val_resp: str = send_command('p', responses['p'], connection_photo)

    if photo_val_resp:
        photo_val =photo_val_resp
