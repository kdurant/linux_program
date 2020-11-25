#-*- coding: UTF-8 -*-
import argparse
import socket
import time

parser = argparse.ArgumentParser(description="simple tcp client program")
parser.add_argument("--ip", default="127.0.0.1", help="tcp client ip address")
parser.add_argument("--port", default=8888, type=int, help="tcp client port")
args = parser.parse_args()

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((args.ip, args.port))

while True:
    client.send(b'hello kdurant\n')
    time.sleep(1)

    #info = client.recv(1024)
    #print("server：",info)
