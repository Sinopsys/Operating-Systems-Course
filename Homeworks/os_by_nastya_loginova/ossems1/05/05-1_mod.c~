#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
char buffer [100];
int fd;

fd=open("myfile", O_RDONLY);

read (fd, buffer, 13);

printf("Information from the file: %s\n", buffer);

printf("File descriptor: %d\n", fd);

close (fd);

exit (0);

}
