#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int see_more();

int main(int ac, char *av[])
{
    FILE * fp;
  
    if(ac == 1) {
        do_more(stdin);
    } else {
        while(--ac) 
        {
            if( (fp=fopen( *++av, "r")) != NULL ) {
                do_more(fp);
                fclose(fp);
            } else {
                exit(1);
            }
        }
    }
    return 0;
}

/* read PAGELEN lines */
void do_more(FILE *fp)
{
    char line[LINELEN];
    int num_of_lines = 0;
    int see_more(FILE *), reply;

    FILE *fp_tty;
    fp_tty = fopen("/dev/tty","r");
    if (fp_tty == NULL)
        exit(1);

    struct termios org_opts, new_opts;
    tcgetattr(STDIN_FILENO, &org_opts);
    memcpy(&new_opts, &org_opts, sizeof(new_opts));
    new_opts.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);

    while (fgets(line, LINELEN, fp))
    {
        if (num_of_lines == PAGELEN) 
        {
            reply = see_more(fp_tty); // user want some more
            if (reply == 0)
                break;
            num_of_lines -= reply;
        }
        if (fputs(line, stdout) == EOF)
            exit(1);
        num_of_lines++;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
}

/* print message, wait for response 
 * q -> no, space -> one page, CR -> one line
*/
int see_more(FILE * cmd)
{
    int c;
    printf("\033[7m more? \033[m");
    while ( (c=getc(cmd)) != EOF )
    {
        if (c == 'q')
            return 0;
        if (c == ' ')
            return PAGELEN;
        if (c == '\n')
            return 1;
    }
    return 0;
}
