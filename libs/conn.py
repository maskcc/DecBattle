import socket
import time
i = 0
sock = []
n =  3000
for x in range(1, n):
    sock.append(socket.socket())
for x in sock: 
    x.connect(("127.0.0.1", 10077))
    #x.connect(("120.25.92.230", 10077))
    #x.connect(("120.25.92.230", 9988))
    #x.connect(("127.0.0.1", 9988))
    #x.connect(("127.0.0.1", 18103))
    if x:
        i = i + 1
        sr = "connect count is" + str(i)
    else:
        sr = "connect error "
    #print(sr)

print("run over")
time.sleep(1200)
