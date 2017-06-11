#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   int     fd[2], result;

   size_t size;
   char  resstring[300];

   if(pipe(fd) < 0){
     printf("Can\'t open pipe\n");
     exit(-1);
   }

   result = fork();

   if(result < 0) {
      printf("Can\'t fork child\n");
      exit(-1);
   } else if (result > 0) {

     /* Parent process */

close(fd[0]);
write(fd[1], resstring, 300);

execlp("ls", "ls", "-al", NULL);
close(fd[1]);

        } else {

      /* Child process */

wait(0);
close(fd[1]);
read(fd[0], resstring, 300);

execl("/bin/grep", "/bin/grep", "05-3", NULL);

close(fd[0]);

   }

   return 0;
}
