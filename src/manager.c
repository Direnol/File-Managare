#include "../headers/manager.h"


int openDir(DIR **dir, char **path)
{
    if (dir == NULL || path == NULL) return EXIT_FAILURE;
    if (*path == NULL) {
        *path = getcwd(NULL, BUF_SIZE);
        if (*path == NULL) return EXIT_FAILURE;
    }

    if (*dir != NULL) {
        closedir(*dir);
    }
    *dir = opendir(*path);
    if (*dir == NULL) return EXIT_FAILURE;
    if (chdir(*path) < 0) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
int compareDir(void *a, void *b)
{
    char *aa = (char *) (a);
    struct dirent *bb = *(struct dirent **) (b);
    printf("[%s] ? [%s]\n", aa, bb->d_name);
    return strcmp(aa, bb->d_name);
}
