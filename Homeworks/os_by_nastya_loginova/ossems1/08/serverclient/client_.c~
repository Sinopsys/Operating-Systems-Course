#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
//#include "shmem.h"
#include <stdio.h>
#include <stdlib.h>


#define MAXBUFF 80
#define PERM 0666

/*Структура данных в разделяемой памяти*/
typedef struct mem_msg {
int segment;
char buff[MAXBUFF];
} Message;


main() {
Message *msgptr;
key_t key;
int shmid, semid;
struct sembuf mybuf2;
struct sembuf mybuf4;
struct sembuf mybuf5;
struct sembuf mybuf6;
struct sembuf mybuf3;
struct sembuf mybuf;
struct sembuf mybuf7;
/* */
if ((key = ftok("client_.c", 0)) < 0) {
 printf("Невозможно получить ключ\n");
 exit(1);
}
/* */
if ((shmid = shmget(key, sizeof(Message), 0)) < 0) {
 printf("Ошибка доступа к разделяемой памяти\n");
 exit(1);
}

/*  */
if ((msgptr = (Message*)shmat(shmid, 0, 0)) < 0) {
 prinf("Ошибка присоединения разделяемой памяти\n");
 exit(1);
}

/*  */
if ((semid = semget(key, 2, PERM)) < 0) {
 printf("Ошибка доступа к семафорам\n");
 exit(1);
}
/*  */
   mybuf.sem_num = 0;
    mybuf.sem_op  = 0;
    mybuf.sem_flg = 0;
if(semop(semid, &mybuf, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1);
}

    mybuf2.sem_num = 0;
    mybuf2.sem_op  = 1;
    mybuf2.sem_flg = 0;

if(semop(semid, &mybuf2, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1);
}
  
    mybuf4.sem_num = 1;
    mybuf4.sem_op  = 1;
    mybuf4.sem_flg = 0;

if(semop(semid, &mybuf4, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1);
}


/*  */
sprintf(msgptr->buff, "Здравствуй мир!\n");

/*  */

    mybuf3.sem_num = 0;
    mybuf3.sem_op  = -1;
    mybuf3.sem_flg = 0;

if(semop(semid, &mybuf3, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1);
}
    mybuf.sem_num = 0;
    mybuf.sem_op  = 0;
    mybuf.sem_flg = 0;
if(semop(semid, &mybuf, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1);
} 

 /*  mybuf6.sem_num = 0;
    mybuf6.sem_op  = 1;
   mybuf6.sem_flg = 0;

if(semop(semid, &mybuf6, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1);
}*/

  mybuf7.sem_num = 0;
    mybuf7.sem_op  = -1;
   mybuf7.sem_flg = 0;

if(semop(semid, &mybuf7, 1) < 0){
      printf("Can\'t wait for condition7\n");
      exit(-1);
}


/* */
if (shmdt(msgptr) < 0) {
 printf("Ошибка отключения разделяемой памяти\n");
 exit(1);
}

/* */
if (shmctl(shmid, IPC_RMID, 0) < 0) {
printf("Незвожно удалить область разделяемой памяти\n");
 exit(1);
}

if (semctl(semid, 0, IPC_RMID) < 0) {
 printf("Невозможно удалить семафоры\n");
 exit(1);
}
exit(0);
}

