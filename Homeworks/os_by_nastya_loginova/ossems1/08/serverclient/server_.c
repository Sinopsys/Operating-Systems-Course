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
Message* msgptr;
key_t key;
int shmid, semid;
struct sembuf mybuf1;
struct sembuf mybuf2;
struct sembuf mybuf3;
struct sembuf mybuf;
/*Получим ключ*/
if ((key = ftok("client_.c", 0)) < 0) {
printf("Невозможно получить ключ\n");
exit(1);
}

/* Создадим область разделяемой памяти */
if ((shmid = shmget(key, sizeof(Message),
 PERM | IPC_CREAT)) < 0) {
 printf("Невозможно создать область\n");
 exit(1);
}
/* Присоединим область*/
if ((msgptr = (Message *)shmat(shmid, 0, 0)) < 0) {
 printf("Ошибка присоединения разделяемой памяти\n");
 exit(1);
}
/* Создадним группу из двух семафоров:
Первый - для синхронизации работы с разделяемой памятью
Второй - для синхронизации выполнения процессов */

if ((semid = semget(key, 2, PERM | IPC_CREAT)) < 0) {
 printf("Невозможно создать семафор\n");
 exit(1);
}

/*Ждём пока клиент начнёт работу и заблокируем раздлеяемую память*/

    mybuf1.sem_num = 1;
    mybuf1.sem_op  = -1;
    mybuf1.sem_flg = 0;

if(semop(semid, &mybuf1, 1) < 0){
      printf("Can\'t wait for condition1\n");
      exit(-1);
}
  mybuf.sem_num = 0;
  mybuf.sem_op  = 0;
  mybuf.sem_flg = 0;
if(semop(semid, &mybuf, 1) < 0){
      printf("Can\'t wait for condition2\n");
      exit(-1);
}
    mybuf2.sem_num = 0;
    mybuf2.sem_op  = 1;
    mybuf2.sem_flg = 0;

if(semop(semid, &mybuf2, 1) < 0){
      printf("Can\'t wait for condition3\n");
      exit(-1);
}

/* Выведем сообщение на терминал*/
printf("%s", msgptr->buff);



   mybuf3.sem_num = 0;
   mybuf3.sem_op  = -1;
  mybuf3.sem_flg = 0;

if(semop(semid, &mybuf3, 1) < 0){
      printf("Can\'t wait for condition4\n");
      exit(-1);
}

/* Отключимся от области*/
if (shmdt(msgptr) < 0) {
 printf("Ошибка отключения\n");
 exit(1);
}
/* Остальную работу по удалению объектов сделает клиент */
exit(0);
return 0;
}


