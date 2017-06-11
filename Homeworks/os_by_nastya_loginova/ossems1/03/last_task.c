#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid, ppid, chpid;
    int a = 0;

    pid = fork();

if (pid == -1){

a=a+3;

} else if (pid == 0){


execle("/bin/cat", "/bin/cat", "main_ex.c", NULL, envp);


} else {



wait (NULL);

a=a+10;
printf("I'm parent\n");
printf("a = %d\n", a);
}
    return 0;

}


