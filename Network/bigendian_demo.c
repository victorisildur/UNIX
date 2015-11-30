#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    int a = 16;
    printf("%d --> ", a);
    printf("%d", htonl(a));
}
