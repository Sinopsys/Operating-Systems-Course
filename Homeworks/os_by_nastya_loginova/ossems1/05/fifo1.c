#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
 
int main ()
{
    int fd;
    size_t size;
 
    (void)umask(0);
 
    if ((fd = mknod("bbb.fifo", S_IFIFO | 0666, 0)) < 0)
    {
       printf("Can\'t create FIFO\n");
       exit(-1);
    }
 
    if ((fd = open("bbb.fifo", O_WRONLY)) < 0)
    {
       printf("Can\'t open FIFO\n");
       exit(-1);
 
    }
 
    size = write(fd, "Hello, me!", 14);
    if (size != 14)
    {
      printf("Can\'t write all string to FIFO\n");
      exit(-1);
    }
 
    return 0;
}

