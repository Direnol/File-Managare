#ifndef FILE_MANAGARE_MANAGER_H
#define FILE_MANAGARE_MANAGER_H

#include "window.h"
#include "file.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include "vector.h"

#define EDITOR "./editor"
#define PATH_EDITOR "/home/direnol/CLionProjects/File-Manager/cmake-build-debug/editor"

#define BUF_SIZE 128

int openDir(DIR **dir, char **path);

int compareDir(void *a, void *b);

void show_manager(WINDOW *w, int y, struct dirent **dir, int n, WINDOW *border, char *cur_dir);

int create_win_manager(WINDOW *parent, WINDOW **win, WINDOW **boxes);

void key_map(WINDOW *win, chtype c, int my);

bool isDir(struct dirent *file);

void cp(char *file, char *to_path);

void * _cp(void *argv);

void load_percent(WINDOW *win, __off_t cur, __off_t all);

WINDOW *init_load_percent();

void del_load_percent(WINDOW *win);

#endif //FILE_MANAGARE_MANAGER_H
