#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
   int     fd1[2], fd2[2], result;

   size_t size;
   char  resstring[14];

   if(pipe(fd1) < 0){
     printf("Can\'t open pipe\n");
     exit(-1);
   }

 if(pipe(fd2) < 0){
     printf("Can\'t open pipe\n");
     exit(-1);
   }

   result = fork();

   if(result < 0) {
      printf("Can\'t fork child\n");
      exit(-1);
   } else if (result > 0) {

     /* Parent process */

      close(fd1[0]);

      size = write(fd1[1], "Hello, from p!", 14);

      if(size != 14){
        printf("Can\'t write all string to pipe\n");
        exit(-1);
      }

      close(fd1[1]);
    printf("Родитель(%d): отправил ребёнку данные\n", getpid());

close(fd2[1]);
      size = read(fd2[0], resstring, 14);

      if(size < 0){
         printf("Can\'t read string from pipe\n");
         exit(-1);
      }


    printf("Родитель (%d): получил %s\n", getpid(), resstring);
      close(fd2[0]);




   } else {

      /* Child process */

      close(fd1[1]);
      size = read(fd1[0], resstring, 14);

      if(size < 0){
         printf("Can\'t read string from pipe\n");
         exit(-1);
      }

    printf("Ребёнок (%d): получил %s\n", getpid(), resstring);

      close(fd1[0]);



   close(fd2[0]);

      size = write(fd2[1], "Hello, fro c!", 14);

      if(size != 14){
        printf("Can\'t write all string to pipe\n");
        exit(-1);
      }

      close(fd2[1]);

    printf("Ребёнок(%d): отправил родителю данные\n", getpid());
   




//exit(1);
   }



   return 0;
}
