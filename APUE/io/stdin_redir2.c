#include <stdio.h>
#include <fcntl.h>

main()
{
    int fd;
    int newfd;
    char line[100];

    fgets(line, 100, stdin); printf("%s", line);
    fgets(line, 100, stdin); printf("%s", line);
    fgets(line, 100, stdin); printf("%s", line);

    fd = open("/etc/passwd", O_RDONLY);
    close(0);
    newfd = dup(fd);

    if (newfd != 0) {
        fprintf(stderr, "could not dup fd to 0");
        exit(1);
    }
    close(fd);

    fgets(line, 100, stdin); printf("%s", line);
    fgets(line, 100, stdin); printf("%s", line);
    fgets(line, 100, stdin); printf("%s", line);
}
