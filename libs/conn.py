import socket
import time
i = 0
sock = []
n = 30000
for x in range(1, n):
    sock.append(socket.socket())
for x in sock: 
    x.connect(("127.0.0.1", 10077))
    if x:
        i = i + 1
        sr = "connect count is" + str(i)
    else:
        sr = "connect error "
    #print(sr)

print("run over")
time.sleep(3)
kk = socket.socket()
kk.connect(("127.0.0.1", 10077))

