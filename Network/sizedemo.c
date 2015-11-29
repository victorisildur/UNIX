#include <stdio.h>

int main()
{
    int intvar, *ptr_intvar;
    char charvar, *ptr_charvar;
    struct st {
        int a;
        char *b;
    };

    struct st stvar;
    struct st * ptr_stvar;
    printf("%d\n", sizeof(intvar));
    printf("%d\n", sizeof(ptr_intvar));
    printf("%d\n", sizeof(charvar));
    printf("%d\n", sizeof(ptr_charvar));
    printf("%d\n", sizeof(stvar));
    printf("%d\n", sizeof(ptr_stvar));
}
