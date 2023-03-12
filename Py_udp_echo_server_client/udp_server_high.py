#! /usr/bin/env python3
"USAGE: %s <port>"

from socketserver import DatagramRequestHandler, UDPServer
from sys import argv

class Echo_Handler(DatagramRequestHandler):
    def handle(self):
        print("Client connected: ", self.client_address)
        message = self.rfile.read()
        self.wfile.write(message)

if len(argv) != 2:
    print(__doc__ % argv[0])
else:
    UDPServer(('', int(argv[1])), Echo_Handler).serve_forever()
