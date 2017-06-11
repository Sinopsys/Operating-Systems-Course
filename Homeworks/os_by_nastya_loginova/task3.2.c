#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

main() {
	char name [] = {"example.fifo"};
	int fd;
	if((fd = open(name, O_RDONLY)) < 0){
        printf("Error ocurred");
	    exit(-1); 
    } 
    char buf[100];
    int size = read(fd, buf, 100);
    printf("I am reader, was printed: %s\n", buf);
    close(fd);
    return 0;
}