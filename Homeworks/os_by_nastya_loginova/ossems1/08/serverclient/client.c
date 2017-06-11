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

/* */
if ((key = ftok("client.c", 0)) < 0) {
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
if (semop(semid, &mem_lock[0], 2) < 0) {
 printf("Невозможно выполнить операцию с семафорами\n");
 exit(1);
}
  
if (semop(semid, &proc_start[0], 1) < 0) {
printf("Невозможно выполнить операцию с семафорами\n");
exit(1);
}

/*  */
sprintf(msgptr->buff, "Здравствуй мир!\n");

/*  */
if (semop(semid, &mem_unlock[0], 1) < 0) {
 printf("Невозможно выполнить операцию с семафорами\n");
 exit(1);
}

if (semop(semid, &proc_start[0], 1) < 0) {
 printf("Невозможно выполнить операцию с семафорами\n");
 exit(1);
}
 
if (semop(semid, &mem_lock[0], 2) < 0) {
 printf("Невозможно выполнить операцию с семафорами\n");
 exit(1);
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

