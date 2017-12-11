//
// Created by direnol on 11.11.17.
//

#ifndef FILE_MANAGARE_WINDOW_H
#define FILE_MANAGARE_WINDOW_H

#include <ncurses.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <panel.h>
#include <stdarg.h>
#include <errno.h>


typedef struct {
    WINDOW *back;
    WINDOW *decor;
    WINDOW *overlay;
    PANEL *panel;
} curw;

curw *tui_new_win(int sy, int sx, int h, int w, char *label, WINDOW *parent);

void tui_new_label(WINDOW *title, char *label);

void _resize_term(int sig);

WINDOW * init();

int err_destruct(char *msg);

void desturct();

int movexy(chtype dir, WINDOW *win, int *cur, int *max);

void refreshTO(WINDOW *w, ...);

void delwinTO(WINDOW *w, ...);

void delcurw(curw *w, ...);

size_t rtrim(char *str, size_t len);

#define try_do(func, msg) if ((func) == ERR) return err_destruct(msg)


#endif //FILE_MANAGARE_WINDOW_H
