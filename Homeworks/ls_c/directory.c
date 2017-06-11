#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <zconf.h>


// Colors for different file types. Custom colors could be added..
//
#define COLOR_DIR "\x1b[34;1m"
#define COLOR_LINK "\x1b[36;1m"
#define COLOR_EXE "\x1b[32;1m"
#define COLOR_DEFAULT "\x1b[m"

// Filter for scandir function, discards a hidden files.
//
int name_filter(const struct dirent *dir)
{
    if (dir->d_name[0] == '.')
    {
        return 0;
    }
    return 1;
}

// Create new string wich contain concatenation of dir_path and fname.
//
static char *make_path(const char *dir_path, const char *fname)
{
    char *path = (char *) malloc(sizeof(char) *
                                 (strlen(dir_path) + strlen(fname) + 1));
    if (!path)
    {
        return path;
    }
    strcpy(path, dir_path);
    if (path[strlen(path) - 1] != '/')
    {
        strcat(path, "/");
    }
    strcat(path, fname);
    return path;
}

// Fills p_str of file permissions.
//
static void make_permissions(struct stat *fstat, char *p_str)
{
    strcpy(p_str, "----------");
    int i = 0;
    mode_t mode = fstat->st_mode;

    if (S_ISDIR(mode))p_str[i] = 'd';
    else if (S_ISLNK(mode))p_str[i] = 'l';
    else if (S_ISFIFO(mode))p_str[i] = 'p';
    else if (S_ISSOCK(mode))p_str[i] = 's';
    else if (S_ISCHR(mode))p_str[i] = 'c';
    else if (S_ISBLK(mode))p_str[i] = 'b';
    else p_str[i] = '-';

    i++;

    if (S_IRUSR & mode)p_str[i] = 'r';
    i++;
    if (S_IWUSR & mode)p_str[i] = 'w';
    i++;
    if (S_IXUSR & mode)p_str[i] = 'x';
    i++;

    if (S_IRGRP & mode)p_str[i] = 'r';
    i++;
    if (S_IWGRP & mode)p_str[i] = 'w';
    i++;
    if (S_IXGRP & mode)p_str[i] = 'x';
    i++;

    if (S_IROTH & mode)p_str[i] = 'r';
    i++;
    if (S_IWOTH & mode)p_str[i] = 'w';
    i++;
    if (S_IXOTH & mode)p_str[i] = 'x';
}

// Create groups string from group structures.
//
static char *make_group(struct stat *fstat)
{
    struct passwd *pw = getpwuid(fstat->st_uid);
    if (pw == NULL) return NULL;

    struct group *gr = getgrgid(fstat->st_gid);
    if (gr == NULL) return NULL;

    int size = (int) (strlen(pw->pw_name) + strlen(gr->gr_name) + 2);
    char *result = (char *) malloc(sizeof(char) * size);
    if (!result) return NULL;

    sprintf(result, "%s %s", pw->pw_name, gr->gr_name);

    return result;
}

// Fill str, (month day hours:minutes).
//
static char *make_time(struct timespec *cal_time, char *str, const size_t size)
{
    struct tm *time;

    time = localtime(&cal_time->tv_sec);
    strftime(str, size, "%h %e %H:%M", time);

    return str;
}

const char *apply_coloring(struct stat filestat, const char *fpath, const char *name)
{
    struct stat sb;
    int size = (int) (strlen(name));
    char *result = (char *) malloc(sizeof(char) * size);

    if (S_ISDIR(filestat.st_mode))
        sprintf(result, COLOR_DIR" %s\n"COLOR_DEFAULT, name);
    else if (!stat(fpath, &sb) && S_ISREG(sb.st_mode) && sb.st_mode & 0111)
        sprintf(result, COLOR_EXE" %s\n"COLOR_DEFAULT, name);
    else
        sprintf(result, " %s\n", name);

    return result;
}

// Reading information about the catalog and formation of the output.
//
int print_dir(const char *path, int list_opt)
{
    // Read dir info to dirent structure.
    //
    int n;
    struct dirent **file_list;
    if ((n = scandir(path, &file_list, &name_filter, alphasort)) < 0)
    {
        perror("Scandir ERROR\n");
        return (EXIT_FAILURE);
    }

    // Formation of the detail or simple output.
    //
    if (list_opt)
    {
        struct stat filestat;
        struct stat stream;
        if (fstat(fileno(stdout), &stream) < 0)
        {
            perror("fstat ERROR\n");
            return (EXIT_FAILURE);
        }
        for (int i = 0; i < n; i++)
        {
            char *fpath = make_path(path, file_list[i]->d_name);
            // Read detailed info about current ellement of the folder.
            //
            if (lstat(fpath, &filestat))
            {
                perror("lstat ERROR\n");
                return (EXIT_FAILURE);
            }

            // Formating strings for detailed output.
            //
            char p_str[11];
            make_permissions(&filestat, p_str);
            char *group = make_group(&filestat);
            if (!group)
            {
                perror("format output ERROR\n");
                return (EXIT_FAILURE);
            }
            char time[30];
            make_time(&filestat.st_mtim, time, sizeof(time));

            printf("%s %lu %s %8lu %s", p_str, filestat.st_nlink,
                   group, filestat.st_size, time);

            if (S_ISLNK(filestat.st_mode))
            {
                char l_path[PATH_MAX];
                readlink(fpath, l_path, sizeof(l_path) - 1);
                if (S_ISCHR(stream.st_mode))
                    printf(COLOR_LINK" %s"COLOR_DEFAULT, file_list[i]->d_name);
                else
                    printf(" %s", file_list[i]->d_name);
                printf(" -> %s\n", l_path);
            } else
            {
                if (S_ISCHR(stream.st_mode))
                    printf(apply_coloring(filestat, fpath, file_list[i]->d_name));
                else
                    printf(" %s\n", file_list[i]->d_name);
            }
            free(file_list[i]);
            free(fpath);
            free(group);
        }
    } else
    {
        // Simple output, without -l option.
        //
        for (int i = 0; i < n; i++)
        {
            printf("%s ", file_list[i]->d_name);
            free(file_list[i]);
        }
        printf("\n");
    }

    return (EXIT_SUCCESS);
}


// EOF
