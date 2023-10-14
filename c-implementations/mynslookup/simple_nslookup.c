#include <stdio.h>
#include <netdb.h>          /* hostent struct, gethostbyname() */
#include <arpa/inet.h>      /* inet_ntoa() for formatting ip address */
#include <netinet/in.h>     /* in_addr struct */
#include <stdlib.h>         /* exit() */

int main (int argc, char **argv) {
    struct hostent *host;       /* host information struct */
    struct in_addr h_addr;      /* internet address */

    if (argc != 2) {
        fprintf(stderr, "USAGE: simple_nslookup <inet_addresss>\n");
        exit(1);
    }

    if ((host = gethostbyname(argv[1])) == NULL) {
            fprintf(stderr, "(nslookup failed on '%s'\n", argv[1]);
            exit(1);
    }

    h_addr.s_addr = *((unsigned long *) host->h_addr_list[0]);
    fprintf(stdout, "%s\n", inet_ntoa(h_addr));
    exit(0);
}
