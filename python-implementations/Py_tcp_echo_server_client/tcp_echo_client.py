#! /usr/bin/env python3
"USAGE: tcp_echo_client.py <server> <word> <port>"

from socket import *
import sys

if len(sys.argv) != 4:
    print(__doc__)
    sys.exit(0)

sock = socket(AF_INET, SOCK_STREAM)
sock.connect((sys.argv[1], int(sys.argv[3])))
message = sys.argv[2]

messlen, received = sock.send(str.encode(message)), 0
if (messlen != len(message)):
    print("Failed to send complete message")
print("Received: ")

while (received < messlen):
    data = sock.recv(32)
    sys.stdout.write(data.decode())
    received += len(data)
print()

sock.close()

