import paho.mqtt.client as mqtt
# import time
# from threading import Thread
import requests

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("e408a1/#")
    print('Subscribe "e408a1/#"')

def on_message(client, userdata, msg):
    topic = msg.topic
    payload = msg.payload.decode('utf-8')
    print(f'{topic}: {payload}')
    if topic == 'e408a1/photoresistor/request':
        value = requests.get(f'http://{host}/photoresistor').text
        client.publish('e408a1/photoresistor', f'{value}')
    elif topic == 'e408a1/air_conditioner/control':
        requests.get(f'http://{host}/{payload}')

'''
e408a1/air_conditioner/control
send_key_17
send_key_20
send_key_22
send_key_24
send_key_26
send_key_shutdown

e408a1/photoresistor/request
photoresistor
'''

host = '192.168.1.100'
def main():
    print('Service start')
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.username_pw_set("*","*")
    client.connect("*", 1883, 60)
    client.loop_forever()
    # Thread(target=client_loop, args=[client,]).start()
    # while True:
    #     pass

# def client_loop(client):
#     client.loop_forever()

if __name__ == '__main__':
    main()
