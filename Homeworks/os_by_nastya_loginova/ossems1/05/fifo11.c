#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int     writefd;
 
   size_t  size;

   char    name[] = "bbb.fifo";
char resstring [14];

(void) umask(0);

   //if(mknod(name, S_IFIFO|O_NDELAY| 0666, 0) < 0){
    // printf("Can\'t create FIFO\n");
    // exit(-1);
  // }

    if((writefd = open(name, O_WRONLY)) < 0){

       printf("Can\'t open FIFO for writting\n");
	 exit(-1);
    }

     size = write(writefd, "Hello, world!", 14);

    if(size != 14){
   printf("Can\'t write all string to FIFO\n");
   exit(-1);

    }
close(writefd);

unlink(name);

   return 0;
}
