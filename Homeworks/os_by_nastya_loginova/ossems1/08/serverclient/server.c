#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "shmem.h"
#include <stdio.h>
#include <stdlib.h>


main() {
Message* msgptr;
key_t key;
int shmid, semid;
/*Получим ключ*/
if ((key = ftok("client.c", 0)) < 0) {
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
if (semop(semid, &proc_wait[0], 1) < 0) {
 printf("Невозможно выполнить операцию\n");
 exit(1);
}

/* new */
//if (semop(semid, &new1[0], 1) < 0) {
// printf("Невозможно выполнить операцию\n");
// exit(1);
//}



/* Ждём пока клиент начнёт запись в разделяемую память и освободит её, потом блокируем */
if (semop(semid, &mem_lock[0], 2) < 0) {
 printf("Невозможно выполнить операцию\n");
 exit(1);
}
/* Выведем сообщение на терминал*/
printf("%s", msgptr->buff);



/* new2 */
//if (semop(semid, &new2[0], 1) < 0) {
// printf("Невозможно выполнить операцию\n");
// exit(1);
//}

/* Освободим разделяемую память */
if (semop(semid, &mem_unlock[0], 1) < 0)
{
 printf("Невозможно освободить память\n");
 exit(1);}

/* Отключимся от области*/
if (shmdt(msgptr) < 0) {
 printf("Ошибка отключения\n");
 exit(1);
}
/* Остальную работу по удалению объектов сделает клиент */
exit(0);
}


