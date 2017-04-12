#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

int main()
{
        char *file_name = "file.txt";
        char buffer[1024];
        int ret_in, open_num;

        if (open_num = open(file_name, O_RDONLY, S_IREAD) == -1) {
                printf("error\n");
        }


        if((ret_in = read (open_num, &buffer, 1024)) != 0) {
                printf(buffer);
        }

        return 0;
}
