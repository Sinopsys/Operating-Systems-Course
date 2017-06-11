#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

main() {
	char name [] = {"example.fifo"};
	if (mknod(name, S_IFIFO | 0666, 0) < 0) {
		printf("Error ocurred");
		exit(-1);
	}
	int fd;
	if((fd = open(name, O_WRONLY)) < 0){
        printf("Error ocurred");
	    exit(-1); 
    } 
    int size = write(fd, "I am writer", 100);
    printf("Writer print: I am writer\n");
    close(fd);
    return 0;
}