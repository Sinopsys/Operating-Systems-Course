#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
 
int main(void)
{
    int fd;
    size_t size;
 
    (void)umask(0);
 
    if ((fd = mknod("MYFIFO", S_IFIFO | 0666, 0)) < 0)
    {
       printf("Can\'t create FIFO\n");
       exit(-1);
    }
 
    if ((fd = open("MYFIFO", O_WRONLY)) < 0)
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

