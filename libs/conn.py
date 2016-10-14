import socket
import time
i = 0
sock = []
n = 20000
for x in range(1, n):
    sock.append(socket.socket())
for x in sock: 
    x.connect(("127.0.0.1", 10001))
    if x:
        i = i + 1
        sr = "connect count is" + str(i)
    else:
        sr = "connect error "
    print(sr)

print("run over")
time.sleep(3)

