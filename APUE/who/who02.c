#include <utmpx.h>
#include <stdio.h>
#include <fcntl.h>

void show_info(struct utmpx * utbufp);
void show_time(long time_sec);

int main()
{
    struct utmpx * records;
    while ( (records = getutxent()) != NULL)
        show_info(records);
    return 0;
}

void show_info(struct utmpx * utbufp)
{
    printf("%s ", utbufp->ut_user);
    printf("%s ", utbufp->ut_id);
    printf("%s ", utbufp->ut_line);
    printf("%d ", utbufp->ut_type);
    show_time(utbufp->ut_tv.tv_sec);
    printf("%s \n", utbufp->ut_host);
}

void show_time(long time_sec)
{
    char * cp;
    cp = ctime(&time_sec);
    printf("%s", cp+4);
}
