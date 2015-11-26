#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define oops(msg) {perror(msg); exit(1);}

main(int ac, char *av[])
{
    struct sockaddr_in servaddr;
    struct hostent     *hp;
    int    sock_id, sock_fd;
    char   message[BUFSIZ];
    int    messlen;
    /* get a socket */
    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_id == -1)
        oops("socket");
    /* connet to server */
    bzero(&servaddr, sizeof(servaddr));
    hp = gethostbyname(av[1]);
    if(hp == NULL)
        oops(av[1]);
    bcopy(hp->h_addr, (struct sockaddr*)&servaddr.sin_addr, hp->h_length);
    servaddr.sin_port = htons(atoi(av[2]));
    servaddr.sin_family = AF_INET;

    if (connect(sock_id, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
        oops("connect");
    /* transfer data from server, then hangup */
    messlen = read(sock_id, message, BUFSIZ);
    if (messlen == -1)
        oops("read");
    if (write(1, message, messlen) != messlen)
        oops("write");
    close(sock_id);
}
