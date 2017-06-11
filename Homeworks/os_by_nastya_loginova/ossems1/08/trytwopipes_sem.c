#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>






int main()
{
   int     fd[2], result;

   size_t size;
   char  resstring1[14];
   char  resstring2[14];
   int   semid;
    char pathname[]="trytwopipes_sem.c";
    key_t key;
    struct sembuf mybuf1;
    struct sembuf mybuf2;
    struct sembuf mybuf3;
    key = ftok(pathname, 0);
    
   if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0){
      printf("Can\'t create semaphore set\n");
      exit(-1);
    }
    
    
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

   
//  close(fd[0]);


    size = write(fd[1], "Hello, from p!", 14);
    

    mybuf1.sem_num = 0;
    mybuf1.sem_op  = 1;
    mybuf1.sem_flg = 0;

if(semop(semid, &mybuf1, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1);

} 

      if(size != 14){
        printf("Can\'t write allllll string to pipe\n");
        exit(-1);
      }

 //close(fd[1]);

    printf("Родитель(%d): отправил ребёнку данные\n", getpid());

   
   

   // close(fd[1]);

    mybuf2.sem_num = 0;
    mybuf2.sem_op  = 0;
    mybuf2.sem_flg = 0;

if(semop(semid, &mybuf2, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1);
}
      size = read(fd[0], resstring2, 14);
 
      if(size < 0){
         printf("Can\'t read string from pipe\n");
         exit(-1);
      }


    printf("Родитель (%d): получил %s\n", getpid(), resstring2);
     // close(fd[0]);




   } else {

      /* Child process */

       // close(fd[1]);


   mybuf3.sem_num = 0;
    mybuf3.sem_op  = -1;
    mybuf3.sem_flg = 0;

if(semop(semid, &mybuf3, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1);
}    
    
      size = read(fd[0], resstring1, 14);
    

      if(size < 0){
         printf("Can\'t read string from p-ipe\n");
         exit(-1);
      }

    printf("Ребёнок (%d): получил %s\n", getpid(), resstring1);

 //   close(fd[0]);

    
 //  close(fd[0]);

    

     size = write(fd[1], "Hello, fro c!", 14);
 
      if(size != 14){
        printf("Child can\'t write all string to pipe\n");
        exit(-1);
      }


   // close(fd[1]);



    printf("Ребёнок(%d): отправил родителю данные\n", getpid());
   






//exit(1);
   }





   return 0;
}
