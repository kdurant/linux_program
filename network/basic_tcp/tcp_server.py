#-*- coding: UTF-8 -*- 
import argparse
import socket

parser = argparse.ArgumentParser(description="simple tcp server program")
parser.add_argument("--ip", default="127.0.0.1", help="tcp server ip address")
parser.add_argument("--port", default=8888, type=int, help="tcp server port")
args = parser.parse_args()

tcpServerSocket = socket.socket()
tcpServerSocket.bind((args.ip, args.port))
tcpServerSocket.listen(5)
while True:
    connection, addr = tcpServerSocket.accept()
    print ('new client addr is : ', addr)
    
    while True:
        data = connection.recv(1024)
        print(data)
    #connection.send(str)

connection.close() 
