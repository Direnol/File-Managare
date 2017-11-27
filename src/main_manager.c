#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include "../headers/manager.h"

int main(int argc, char **argv)
{
    DIR *dir = NULL;
    char *path = malloc(256 * sizeof(char));
    struct dirent **list;
    getcwd(path, 256);

    bool cur_window = 0;
    openDir(&dir, &path);
    while(1) {
        int n = scandir(path, &list, 0, alphasort);

        for (int i = 0; i < n; ++i) printf("%s\n", list[i]->d_name);
        fgets(path, 257, stdin);
        if (!strcmp(path, "-1")) break;
        path[strlen(path) - 1] = '\0';
        struct dirent *ff;
        ff = *(struct dirent **) bsearch(path, list, n - 1, sizeof(ff), (__compar_fn_t) compareDir);
        if (ff) {
            openDir(&dir, &path);
            free(list);
            list = NULL;
        } else {
            printf("[%s] not founded\n", path);
        }
    }

    if (list) free(list);
    free(path);
    closedir(dir);
    return EXIT_SUCCESS;
}