#include <utmpx.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
    struct utmpx record;
    int fd;
    int reclen = sizeof(record);
    if ( (fd=open(UTMPX_FILE,O_RDONLY)) == -1) {
        perror(UTMPX_FILE);
        exit(1);
    }
    while (read(fd, &record, reclen) == reclen)
        show_info(&record);
    close(fd);
    return 0;
}

show_info(struct utmpx * utbufp)
{
    printf("%s\n", utbufp->ut_user);
}
