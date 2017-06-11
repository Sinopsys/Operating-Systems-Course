#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define MAX_BUF 1024

int main(void)

puts ("Server - listening");

int code = mkfifo("demo_fifo", 0666);

int fd = open("demo_fifo", O_RDONLY);

puts("FIFO OPEN");

char stringBuffer [256];
memset(stringBuffer, 0, 256);

int res;
char Len;
while (1){
res = read(fd, &Len, 1);
if (res==0){
break;
}
read(fd, stringBuffer, Len);
stringBuffer[(int)Len] = 0;
printf("Server received: %s\n", stringBuffer);
}
putd("EOF found");

close(fd);
    return 0;
}

