#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(void)
{

puts("Client");    

char strMessage [] = {"Welcome", "to", "STOP"};

int fd = open("demo_fifo", O_WRONLY);

for (unsigned int n=0; n<8; n++)
{
char L = (char)strlen(strMessage[n]);
write(fd, &L, 1);
write(fd, strMessage[n], strlen(strMessage[n]));

    close(fd);

    return 0;
}

