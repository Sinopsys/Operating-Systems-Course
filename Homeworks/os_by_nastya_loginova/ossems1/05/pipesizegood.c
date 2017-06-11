#include <unistd.h>
#include <errno.h>
#include </usr/include/linux/fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/stat.h>

void main()
{
  int fd ;
  long pipesize;
  char name[]="aaa.fifo";
  (void)umask(0); 
  if(mknod(name, S_IFIFO | 0666, 0) < 0){
     printf("Can\'t create FIFO\n");
     exit(-1); 
  }
  else {
    fd = open( name, O_RDONLY|O_NONBLOCK );
  }

  fprintf( stderr, "Size of pipe is %ld bytes\n", (long)fcntl( fd, F_GETPIPE_SZ ));
  if( errno )fprintf( stderr, "Uh oh, errno is %d\n", errno );
  if( fd )close( fd );
}
