#ifndef FILE_MANAGARE_EDITOR_H
#define FILE_MANAGARE_EDITOR_H

#include "window.h"
#include "file.h"

int keymap(WINDOW *win, chtype key, int *cur, int *max);

int saveF2(WINDOW *win, int fd, int max_pos, char *name);

int openF1(WINDOW *win, int *fd, int *cur, int *max, char *name);

int ctrl(WINDOW *win, int *cur, int *max);


#endif //FILE_MANAGARE_EDITOR_H
