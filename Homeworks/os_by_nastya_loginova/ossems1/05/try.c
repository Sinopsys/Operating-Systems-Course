#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[])
{
   int     fd[2], result;

   size_t size;
   char  resstring[14];

   if(pipe(fd) < 0){
     printf("Can\'t open pipe\n");
     exit(-1);
   }

   result = fork();

   if(result < 0) {
      printf("Can\'t fork child\n");
      exit(-1);
   } else if (result == 0) {

     /* Child process */

      printf("This is child\n");
      execlp("ls", "ls", "-al", NULL);

   } else {

      /* Parent process */

      close(fd[1]);
      size = read(fd[0], resstring, 140);

      printf("%s\n", resstring);

      close(fd[0]);
   }

   return 0;
}
