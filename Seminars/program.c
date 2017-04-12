#include <stdio.h>
#include <unistd.h>

int main(){
        printf("%d\n", fork());
        printf("%s: %d, %s: %d\n", "process id", getpid(), "parent id", getppid());

        execl("/bin/ls", "ls", "-l", (char *)0);
        return 0;
}
