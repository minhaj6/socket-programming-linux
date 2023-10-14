#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>

#define MAXPENDING  5       /* number of max queued connections */
#define BUFFSIZE    32

void Die(char *mess) { perror(mess); exit(1); }

void HandleClient(int sock) {
    char buffer[BUFFSIZE];
    int received = -1;

    /* receive message */
    if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) {
        Die("Failed to receive intial bytes from client");
    }

    /* send bytes and check for more incoming data */
    while (received > 0) {
        /* echo the received data */
        if (send(sock, buffer, received, 0) != received) {
            Die("Failed to send bytes to client");
        }

        /* check for more data */
        if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) {
            Die("Failed to receive additional bytes from client");
        }
    }
    close(sock);
}

int main(int argc, char *argv[]) {
    int serversock, clientsock;
    struct sockaddr_in echoserver, echoclient;

    if (argc != 2) {
        fprintf(stderr, "USAGE: tcp_echo_server <port>\n");
        exit(1);
    }

    /* create the tcp socket */
    if ((serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        Die("Failed to create socket");
    }

    /* construct the server sockaddr_in struct */
    memset(&echoserver, 0, sizeof(echoserver));     /* clears struct */
    echoserver.sin_family = AF_INET;
    echoserver.sin_addr.s_addr = htonl(INADDR_ANY); /* any incoming address */
    echoserver.sin_port = htons(atoi(argv[1]));     /* server port */

    /* bind the server socket */
    if (bind(serversock, (struct sockaddr *) &echoserver,
                        sizeof(echoserver)) < 0) {
        Die("Failed to bind the server socket");
    }

    /* listen on the server socket */
    if (listen(serversock, MAXPENDING) < 0) {
        Die("Failed to listen on server socket");
    }

    while(1) {
        unsigned int clientlen = sizeof(echoclient);
        /* wait for client connection */
        if ((clientsock = 
                    accept(serversock, (struct sockaddr *) &echoclient,
                        &clientlen)) < 0) {
            Die("Failed to accept client connection");
        }
        fprintf(stdout, "Client connected: %s\n",
                inet_ntoa(echoclient.sin_addr));
        HandleClient(clientsock);
    }
}



