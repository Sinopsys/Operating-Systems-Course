#include <stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char* argv[])
{
int fd[2];
ssize_t size;
char resstring[14]={"HELLO, WORLD!"};

fd[0] = atoi(argv[1]);
fd[1] = atoi(argv[2]);

close(fd[0]);
size=write(fd[1],resstring,14);
if (size!=14)
{
printf("Can't write all string\n");
exit(-1);
}
close(fd[1]);
return 0;
}

