nslookup is a tool for querying domain name system for mapping between domain name and ip address or other dns records. These are minimum (but not so barebone - since it depends heavily on other libraries) implementation for nslookup. 

```
#include <netdb.h>          /* hostent struct, gethostbyname() */
#include <arpa/inet.h>      /* inet_ntoa() for formatting ip address */
#include <netinet/in.h>     /* in_addr struct */
```

```
man netdb.h
man arpa_inet.h
man netinet_in.h
```
