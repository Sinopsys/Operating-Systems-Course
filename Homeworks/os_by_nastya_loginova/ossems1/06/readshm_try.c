#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
int *buf;
int shmid, flag;
key_t key;
int fd;
if((key = ftok("writeshm_try.c", 0)) < 0){
printf("Can't generate key\n");
exit(0);
}
if((shmid = shmget(key, sizeof(int), 0)) < 0){
printf("Can't find shared memory\n");
exit(0);
}
if((buf = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){
printf("Can't attach shared memory\n");
exit(0);
}
int i;
i = 0;
printf("writeshm_try.c:\n");
printf("The content of the file:\n\n");

while (buf[i] != EOF ){
putchar(buf[i]);
++i;
}
if(shmctl(shmid, IPC_RMID, NULL) < 0){
printf("Can't free shared memory\n");
exit(-1);
}
printf("\nAll shared mamory released\n\n");
return 0;
} 


