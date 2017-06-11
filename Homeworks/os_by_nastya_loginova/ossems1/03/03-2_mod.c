#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{

    execl("/bin/cat", "/bin/cat", "03-2.c", NULL);

    printf("Error on program start\n");
    exit(-1);

    return 0;
}

