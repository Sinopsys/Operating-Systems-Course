# include "stdio.h"




main (int argc, char *argv[], char *envp[])

{

while (*envp)
printf("argc = %d, argv = %s, envp = %s\n", argc, argv[0], *envp++);


return 0;
}


