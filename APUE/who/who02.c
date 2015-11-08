#include <utmpx.h>
#include <stdio.h>
#include <fcntl.h>

void show_info(struct utmpx * utbufp);

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
    printf("%s \n", utbufp->ut_host);
}
