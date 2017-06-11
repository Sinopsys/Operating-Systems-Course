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
int shmid, fd, flag;
key_t key;
if((key = ftok("writeshm_try.c", 0)) < 0){
printf("Can't generate key\n");
exit(-1);
}

if((shmid = shmget(key, 10000*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0){
if(errno != EEXIST){
printf("Can't create shared memory\n");
exit(-1);
}
else {
if((shmid = shmget(key, 10000*sizeof(int), 0)) < 0){
printf("Can't find shared memory\n");
exit(-1);
}
}
}
if((buf = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){
printf("Can't attach shared memory\n");
exit(-1);
}
int i;
i = 0;
fd = open ("writeshm_try.c", O_RDONLY);


while ((flag = read (fd, &buf[i], 1)) > 0){
i++;
}
buf[i+1]=EOF;
if (flag < 0){
printf ("Can't read file\n");
exit (1);
}
if(shmdt(buf) < 0){
printf("Can't detach shared memory\n");
exit(-1);
}
printf("\nThe text of the program was written\n\n");
return 0;
} 
 
