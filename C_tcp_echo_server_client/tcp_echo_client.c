#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUFFSIZE 32

void Die(char *mess) { perror(mess); exit(1);}

int main (int argc, char *argv[]) {
    int sock;
    struct sockaddr_in echoserver;
    char buffer[BUFFSIZE];
    unsigned int echolen;
    int received = 0;

    if (argc != 4) {
        fprintf(stderr, "USAGE: tcp_echo_client <server_ip> <word> <port>\n");
        exit(1);
    }

    /* creating the socket */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        Die("Failed to create socket");
    }

    /* construct sockaddr_in struct for connection */
    memset(&echoserver, 0, sizeof(echoserver));         /* clears struct */
    echoserver.sin_family = AF_INET;
    echoserver.sin_addr.s_addr = inet_addr(argv[1]);    /* ip address */
    echoserver.sin_port = htons(atoi(argv[3]));          /* server port */

    /* establish connection */
    if (connect(sock, (struct sockaddr *) &echoserver,
                sizeof(echoserver)) < 0) {
        Die("Failed to connect to the server");
    }

    /* send data to the server */
    echolen = strlen(argv[2]);
    if (send(sock, argv[2], echolen, 0) != echolen) {
        Die("Mismatch in number of sent bytes");
    }

    /* receive data back from the server */
    fprintf(stdout, "Received: ");
    while (received < echolen) {
        int bytes = 0;
        if ((bytes = recv(sock, buffer, BUFFSIZE-1, 0)) < 1) {
            Die("failed to receive bytes from the server");
        }
        received += bytes;
        buffer[bytes] = '\0';           /* assure null terminated string */
        fprintf(stdout, buffer);
    }
    
    /* close the socket */
    fprintf(stdout, "\n");
    close(sock);
    exit(0);

}

