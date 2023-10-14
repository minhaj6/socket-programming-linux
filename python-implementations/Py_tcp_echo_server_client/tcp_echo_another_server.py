#!/usr/bin/env python3
"USAGE: tcp_echo_another_server.py <port>"

from socket import *
import sys

def handle_client(sock):
    data = sock.recv(32)
    while data:
        sock.sendall(data)
        data = sock.recv(32)
    sock.close()

if len(sys.argv) != 2:
    print(__doc__)
else:
    sock = socket(AF_INET, SOCK_STREAM)
    sock.bind(('',int(sys.argv[1])))
    sock.listen(5)

    while True:
        newsock, client_addr = sock.accept()
        print("Client connected: ", client_addr)
        handle_client(newsock)
