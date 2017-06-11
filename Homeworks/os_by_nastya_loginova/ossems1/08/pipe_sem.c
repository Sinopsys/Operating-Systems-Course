#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/sem.h>


int main()
{
   int     fd[2], result;
   size_t size;
   char  resstring[14];

   if(pipe(fd) < 0){
     printf("Can\'t open pipe\n");
     exit(-1);
   }


////семафор



   int     semid;
   char    pathname[] = "pipe_sem.c";
   key_t   key;
   struct sembuf mybuf;

 key = ftok(pathname, 0);
    
    if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0){
      printf("Can\'t create semaphore set\n");
      exit(-1);
    }
 

// семафор 1   
    mybuf.sem_op  = 1;
    mybuf.sem_num = 0;
    mybuf.sem_flg = 0;
    
    if(semop(semid, &mybuf, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1);
    }  
  
//передаём в канал строку

 close(fd[0]);

      size = write(fd[1], "Hello, world!", 14);

      if(size != 14){
        printf("Can\'t write all string to pipe\n");
        exit(-1);
      }

 //    close(fd[1]);
      

//блокируем процесс пока семафор не станер равен 0


    mybuf.sem_num = 0;
    mybuf.sem_op  = -1;
    mybuf.sem_flg = 0;

if(semop(semid, &mybuf, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1);
    }  
  

//после разблокировки читаем и выводим строку

  
    close(fd[1]);
      size = read(fd[0], resstring, 14);

      if(size < 0){
         printf("Can\'t read string from pipe\n");
         exit(-1);
      }

      printf("%s\n", resstring);

 //   close(fd[0]);
   

   return 0;
}
