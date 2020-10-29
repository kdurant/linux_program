#-*- coding: UTF-8 -*- 
import socket
import time
 
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(("127.0.0.1",8888))
 
while True:
    client.send(b'hello kdurant\n')
    time.sleep(1)

    #info = client.recv(1024)
    #print("server：",info)
