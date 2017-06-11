#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    int fd;
    char * myfifo = "/home/alice/myfifo";
//(void)umask(0);

    /* create the FIFO (namcded pipe) */
  //  mkfifo(myfifo, O_NDELAY|0666);

    /* write "Hi" to the FIFO */
    fd = open(myfifo, O_WRONLY);
    write(fd, "ffddffddffddf!", 14);
    close(fd);

    /* remove the FIFO */
   unlink(myfifo);
exit(1);
    return 0;
}

