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

void _resize_term(int sig);

int init(PANEL *enter);

int err_destruct(char *msg);

void desturct();

int movexy(chtype dir, WINDOW *win, int *cur, int *max);
#define try_do(func, msg) if ((func) == ERR) return err_destruct(msg)


#endif //FILE_MANAGARE_WINDOW_H
