#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

# define FIFO "fifo.1"

main ()
{
int writefd, n;

//char buff[100];


if (mknod(FIFO, S_IFIFO | 0666, 0)<0) 
{
printf ("Невозможно создать FIFO\n"); 
exit (1); }

if ((writefd = open(FIFO, O_WRONLY))<0)
{
printf ("Невозможно открыть FIFO\n"); 
exit (1); }


if (write(writefd, "Hello, Alisa!\n", 14) !=14){
printf ("Ошибка записи\n"); exit (1);}

printf("process pid: %d", getpid());

   printf("process ppid: %d\n", getppid());



//close (writefd);

//unlink(FIFO);

//exit (0);
return(0);
}
