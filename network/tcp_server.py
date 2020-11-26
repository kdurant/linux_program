#-*- coding: UTF-8 -*-
import argparse
import socket

parser = argparse.ArgumentParser(description="simple tcp server program")
parser.add_argument("--ip", default="127.0.0.1", help="tcp server ip address")
parser.add_argument("--port", default=8888, type=int, help="tcp server port")
args = parser.parse_args()

server = socket.socket()
server.bind((args.ip, args.port))
server.listen(5)
while True:
    print("wait for new tcp client to connect...")
    connection, addr = server.accept()
    print('new client addr is : {0}'.format(addr))

    while True:
        data = connection.recv(1024)
        if not data:
            print("client actively disconnects the socket")
            break
        print(data)
    connection.close()
