#!/usr/bin/env python3
"USAGE: %s <server> <word> <port>"

from socket import *
from sys import argv, exit

if len(argv) != 2:
    print(__doc__ % argv[0])
    exit()

sock = socket(AF_INET, SOCK_DGRAM)
sock.bind(('', int(argv[1])))
while True:
    message, client = sock.recvfrom(256) # 256 byte datagram
    print("Client connected: ", client)
    sock.sendto(message, client)


