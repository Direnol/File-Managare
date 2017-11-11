//
// Created by direnol on 11.11.17.
//

#include "window.h"
int init()
{


    if (initscr() == NULL) return EXIT_FAILURE;

    if (noecho() == ERR) return EXIT_FAILURE;
    if (box(stdscr, 0, 0) == ERR) return EXIT_FAILURE;
    if (keypad(stdscr, TRUE) == ERR) return EXIT_FAILURE;
    signal(SIGWINCH, _resize_term);
    if (refresh() == ERR) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
void desturct()
{
    endwin();
}
int err_destruct(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    desturct();
    return EXIT_FAILURE;
}

void _resize_term(int sig)
{
    struct winsize size;
    ioctl(1, TIOCGWINSZ, (char *)&size);
    resizeterm(size.ws_row, size.ws_col);
    refresh();
}
