//
// Created by direnol on 11.11.17.
//

#include "window.h"
int init(PANEL *enter)
{
    if (initscr() == NULL) return EXIT_FAILURE;

    if (noecho() == ERR) return EXIT_FAILURE;
    if (keypad(stdscr, TRUE) == ERR) return EXIT_FAILURE;
    signal(SIGWINCH, _resize_term);
    WINDOW *panel = newwin(3, getmaxx(stdscr),
        getmaxy(stdscr) - 3, 0);
    if (!panel) return EXIT_FAILURE;
    if (box(panel, 0, 0) == ERR) return EXIT_FAILURE;
    mvwprintw(panel, 1, 1, "F5-open|F2-save|F3-exit");
    if (box(stdscr, 0, 0) == ERR) return EXIT_FAILURE;
    if (refresh() == ERR) return EXIT_FAILURE;
    wrefresh(panel);
    delwin(panel);
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
void movexy(chtype dir, WINDOW *win)
{
    int x, y;
    getyx(win, y, x);
    switch (dir) {
        case (KEY_RIGHT): {
            wmove(win, y, x + 1);
            break;
        }
        case (KEY_LEFT): {
            wmove(win, y, x - 1);
            break;
        }
        case (KEY_UP): {
            wmove(win, y - 1, x);
            break;
        }
        case (KEY_DOWN): {
            wmove(win, y + 1, x);
            break;
        }
    }
}
