#include <stdlib.h>
#include <stdio.h>
#include "directory.h"

void print_usage()
{
    printf("Usage: ls -l directory.\n");
    printf("If no directory provided, current will be listed.\n");
}

int main(int argc, const char *argv[])
{
    int list_opt = 0;

    if (argv[1][0] == '-')
    {
        if (argv[1][1] == 'l')
            list_opt = 1;
        else
        {
            print_usage();
            return (EXIT_FAILURE);
        }
    } else
    {
        print_usage();
        return (EXIT_FAILURE);
    }


    const char *path;
    if (argc == 1 || argv[argc - 1][0] == '-')
    {
        // If path not provided then set path to current folder.
        //
        path = "./";
    } else
    {
        path = argv[argc - 1];
    }

    print_dir(path, list_opt);

    return (EXIT_SUCCESS);
}


// EOF
