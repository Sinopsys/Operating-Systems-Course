#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
int *ptr;
int md, flag;
key_t key;
int fd;
if((key = ftok("writeshm.c", 0)) < 0){
printf("Can\'t generate key\n");
//exit(0);
}
if((md = shmget(key, 8192*sizeof(int), 0)) < 0){
printf("Can\'t find shared memory\n");
//exit(0);
}
if((ptr = (int *)shmat(md, NULL, 0)) == (int *)(-1)){
printf("Can't attach shared memory\n");
//exit(0);
}
int i;
i = 0;
printf("write.c:\n");
printf("-----------------------------------------------------------\n\n");
while (ptr[i] != EOF ){
putchar(ptr[i]);
++i;
}
if(shmctl(md, IPC_RMID, NULL) < 0){
printf("Can't free shared memory\n");
//exit(0);
}
printf("\nAll shared mamory released\n\n");
return 0;
} 

