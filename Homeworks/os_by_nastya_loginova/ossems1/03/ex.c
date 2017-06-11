#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {


printf ("\n User ID %d\n", getuid());

printf ("\n Group ID %d\n", getgid());

}
