#!/usr/bin/env python3
"USAGE: %s <server> <word> <port>"
from socket import *
from sys import argv, exit

if len(argv) != 4:
    print(__doc__ % argv[0])
    exit(0)

sock = socket(AF_INET, SOCK_DGRAM)
mess_out = argv[2]
sock.sendto(mess_out.encode(), (argv[1], int(argv[3])))
mess_in, server = sock.recvfrom(255)
if (mess_in.decode() != mess_out):
    print("Failed to receive identical message")
print("Received: ", mess_in)
sock.close()
