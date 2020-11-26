#-*- coding: UTF-8 -*-
import argparse
import socket
import time

parser = argparse.ArgumentParser(description="simple tcp client program")
parser.add_argument("--ip", default="127.0.0.1", help="remote tcp server ip address")
parser.add_argument("--port", default=8888, type=int, help="remote tcp client port")
parser.add_argument("-t", "--timeout", default=0, type=int, help="tcp client timeout")
args = parser.parse_args()

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((args.ip, args.port))

if args.timeout == 0:
    client.settimeout(None)
else:
    client.settimeout(args.timeout)
#while True:
#client.send(b'hello kdurant\n')
#time.sleep(1)

#info = client.recv(1024)
#print("server：",info)

while True:
    try:
        data = client.recv(2048)

    except socket.timeout:
        print("There are no data in {0}s. Close socket.".format(args.timeout))
        client.close()
        break
