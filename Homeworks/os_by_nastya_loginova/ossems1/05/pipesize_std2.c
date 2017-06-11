#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int fd[2], result;
	size_t size;



	if (pipe(fd) < 0) {
		printf("Can't open pipe\n");
		exit(-1);
	}



	int count = 0;

	if (fcntl(fd[1], F_SETFL, O_NONBLOCK) == -1) {
		fprintf(stderr, "Call to fcntl failed.\n"); 
		exit(1);
	}

	while (write(fd[1], "1", 1) > 0) {
		count++;
		printf("Bytes written to pipe: %d\n", count);
	}

	printf("Pipe size is: %d\n", count);

	close(fd[1]);
	close(fd[0]);
}