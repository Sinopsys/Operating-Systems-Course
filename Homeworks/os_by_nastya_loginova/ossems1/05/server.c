#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

# define FIFO "fifo.1"
# define MAXBUFF 80
main ()
{
int readfd, n;

char buff[MAXBUFF];


if ((readfd = open(FIFO, O_RDONLY))<0)
{
printf ("Невозможно открыть FIFO\n"); 
exit (1); }

while ((n=read(readfd, buff, MAXBUFF))>0)
if (write(1, buff, n) !=n){
printf ("Ошибка вывода\n"); exit (1);}

printf ("Текст из FIFO:%s\n", buff);

printf("process pid: %d", getpid());

   printf("process ppid: %d\n", getppid());


close (readfd);

exit (0);

return(0);
}
