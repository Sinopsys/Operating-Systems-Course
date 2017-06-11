#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

pid_t pid, ppid;

pid = getpid ();
ppid = getppid ();

printf ("PID = %d\nPPID = %d\n", (int)pid, (int)ppid);


}
