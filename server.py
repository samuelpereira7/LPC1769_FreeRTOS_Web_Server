import requests
import time
import datetime
import json
import paho.mqtt.publish as publish

def publish_sensor(mes):
    publish.single("plane", mes, hostname="localhost")

while(1):
    ac_const = 90/65
    r = requests.get('http://192.168.0.87:80')
    resp = str(r.content).split(',')
    payload = {}
    payload['x'] = int(int(resp[1]) * ac_const)
    payload['y'] = int(int(resp[2]) * ac_const)
    payload['z'] = int(int(resp[3]) * ac_const)
    payload['t'] = resp[4]

    str_payload = json.dumps(payload)
    print(str(datetime.datetime.now()) + ' - ' + str_payload + ' - published')
    print

    publish_sensor(str_payload)
    time.sleep(10)