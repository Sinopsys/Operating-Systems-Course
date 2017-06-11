#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int     fd[2], fd1[2], result;

   size_t size;
   char  resstring[22];

   if(pipe(fd) < 0){
     printf("Can\'t open pipe\n");
     exit(-1);
   }

 if(pipe(fd1) < 0){
     printf("Can\'t open pipe\n");
     exit(-1);
   }

   result = fork();

   if(result < 0) {
      printf("Can\'t fork child\n");
      exit(-1);
   } else if (result > 0) {

     /* Parent process */


     size = write(fd[1], "From parent to child!", 22);
      size = read(fd1[0], resstring, 22);

      if(size != 14){
        printf("Can\'t write all string to pipe\n");
        exit(-1);
      }
      close(fd[0]);
      close(fd[1]);
      printf("Parent exit\n");
      printf("resstring:%s\n", resstring);

   } else {


      /* Child process */

     size = write(fd[1], "From child to parent!", 22);
      size = read(fd[0], resstring, 22);

      if(size < 0){
         printf("Can\'t read string from pipe\n");
         exit(-1);
      }
      printf("resstring:%s\n", resstring);
      printf("Child exit, resstring:%s\n", resstring);
      close(fd[1]);
      close(fd[0]);
   }



   return 0;
}
