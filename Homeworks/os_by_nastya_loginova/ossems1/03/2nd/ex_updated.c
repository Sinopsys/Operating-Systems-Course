#include <stdio.h>

#include <unistd.h>

int main() {

uid_t uid; 
gid_t gid;

uid = getuid ();
gid = getgid ();

printf ("User ID = %d\nGroup ID = %d\n ", (int)uid, (int)gid);


}
