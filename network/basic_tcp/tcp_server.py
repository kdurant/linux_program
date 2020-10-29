import socket

tcpServerSocket=socket.socket()
host = socket.gethostname()
print(host)
port=8888
tcpServerSocket.bind((host,port))
tcpServerSocket.listen(5)
while True:
    
    
    c, addr = tcpServerSocket.accept()       
    print ('client addr is : ', addr)
    str = 'hello client'
    #c.send(str)
    c.close() 
