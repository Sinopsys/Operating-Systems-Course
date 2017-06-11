#include <stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

int main( int argc, char *argv[])
{
int fd[2], result1;
char fd0[8], fd1[8];
char resstring[14];
ssize_t size;
pipe(fd);
result1=fork();
if (result1 < 0)
{
printf("Can't fork child2\n");
exit(-1);
}
if (result1==0)
{
printf("This is child\n");
snprintf(fd0, sizeof(fd0), "%d", fd[0]);
snprintf(fd1, sizeof(fd1), "%d", fd[1]);
execl("./333", "333", fd0, fd1, NULL);
}

// printf("This is child1\n");
if(result1>0){
close(fd[1]);
size=read(fd[0],resstring,140);
close(fd[0]);
printf("%s", resstring);
}
return 0;
}

