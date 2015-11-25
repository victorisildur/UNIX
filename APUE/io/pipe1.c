#include <stdio.h>
#include <unistd.h>

#define oops(m, x) {perror(m);exit(x);}

main(int ac, char **av){
    int thepipe[2], newfd, pid;
    if (ac != 3) {
        fprintf(stderr, "usage: pipe cmd1 cmd2\n");
        exit(1);
    }
    if (pipe(thepipe) == -1)
        oops("cannot get a pipe", 1);
    if ( (pid = fork()) == -1)
        oops("cannot fork", 2);
    
    /* parent process
     * cmd2, its stdin modified to thepipe[0]
     */
    if (pid > 0) 
    {
        close(thepipe[1]);
        if (dup2(thepipe[0],0) == -1)
            oops("could not redirent stdin", 3);
        close(thepipe[0]);
        execlp(av[2], av[2], NULL);
        oops(av[2], 4);
    }
    /* child process
     * cmd1, its stdout modified to thepipe[1]
     */
    else
    {
        close(thepipe[0]);
        if (dup2(thepipe[1],1) == -1)
            oops("could not redirect stdout", 4);
        close(thepipe[1]);
        execlp(av[1], av[1], NULL);
        oops(av[1], 5);
    }
}
