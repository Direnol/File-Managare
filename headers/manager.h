#ifndef FILE_MANAGARE_MANAGER_H
#define FILE_MANAGARE_MANAGER_H

#include "window.h"
#include "file.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "vector.h"

#define BUF_SIZE 128

int openDir(DIR **dir, char **path);

int compareDir(void *a, void *b);



#endif //FILE_MANAGARE_MANAGER_H
