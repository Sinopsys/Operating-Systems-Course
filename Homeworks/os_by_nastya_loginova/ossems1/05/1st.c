#include <stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

int main( int argc, char *argv[])
{
int fd[2], result;
char fd0[14], fd1[14];
char resstring[14];
ssize_t size;

pipe(fd);
result=fork();
if (result < 0)
{
printf("Can't fork child2\n");
exit(-1);
}
if (result==0)
{

printf("This is child\n");



execl("second", "./second", NULL);
}


if(result>0){

close(fd[1]);
size=read(fd[0],resstring,140);
close(fd[0]);
printf("%s", resstring);
}
return 0;
}

