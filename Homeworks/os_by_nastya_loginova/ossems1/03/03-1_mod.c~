#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main()
{
    pid_t fork_result, pid, ppid;
    int a = 0;

    fork_result = fork();

if (fork_result == -1){

a=a+3;

} else if (fork_result == 0){

a=a+8;

} else {

a=a+12;

}

    pid  = getpid();
    ppid = getppid();

    printf("My pid = %d, my ppid = %d, result = %d\n", (int)pid, (int)ppid, a);


    return 0;

}


