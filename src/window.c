//
// Created by direnol on 11.11.17.
//

#include "../headers/window.h"
int init(WINDOW *enter, size_t count_windows)
{
    if (initscr() == NULL) return EXIT_FAILURE;

    if (noecho() == ERR) return EXIT_FAILURE;
    if (keypad(stdscr, TRUE) == ERR) return EXIT_FAILURE;
    signal(SIGWINCH, _resize_term);
    WINDOW *panel = newwin(3, getmaxx(stdscr),
        getmaxy(stdscr) - 3, 0);
    if (!panel) return EXIT_FAILURE;
    if (box(panel, 0, 0) == ERR) return EXIT_FAILURE;
    mvwprintw(panel, 0, 0, "F1-open|F2-save|F3-exit");
    if (box(stdscr, '|', '=') == ERR) return EXIT_FAILURE;
    if (refresh() == ERR) return EXIT_FAILURE;
    wrefresh(panel);
    delwin(panel);
    enter = newwin(getmaxy(stdscr) - 4, getmaxx(stdscr) - 2, 1, 1);
    if (!enter) return EXIT_FAILURE;
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
int movexy(chtype dir, WINDOW *win, int *cur, int *max)
{
    int x, y;
    getyx(win, y, x);
    int maxx, maxy;
    getmaxyx(win, maxy, maxx);
    switch (dir) {
        case (KEY_RIGHT): {
            if (*cur == *max) return EXIT_FAILURE;
            if (x == maxx - 1 || winch(win) == '\n') {
                ++y;
                x = -1;
            }
            ++(*cur);
            wmove(win, y, x + 1);
            break;
        }
        case (KEY_LEFT): {
            if (*cur == 0) return EXIT_FAILURE;
            if (x == 0 && y != 0) {
                --y;
                x = maxx;
            }
            --(*cur);
            wmove(win, y, x - 1);
            break;
        }
        case (KEY_UP): {
            //wmove(win, y - 1, x);
            int tx = x, ty = y - 1;
            if (y == 0) return EXIT_FAILURE;
            int tmp = *cur;
            movexy(KEY_LEFT, win, cur, max);
            do {
                getyx(win, y, x);
                if (y == ty && tx == x) break;
            } while (!movexy(KEY_LEFT, win, cur, max));
            if (ty != y) {
                wmove(win, ty + 1, tx);
                *cur = tmp;
            }
            break;
        }
        case (KEY_DOWN): {
            if (y == maxy) return EXIT_FAILURE;
            int tx = x, ty = y + 1;
            int tmp = *cur;
            movexy(KEY_RIGHT, win, cur, max);
            do {
                getyx(win, y, x);
                if (y == ty && tx == x) break;
            } while (!movexy(KEY_RIGHT, win, cur, max));
            if (ty != y) {
                wmove(win, ty - 1, tx);
                *cur = tmp;
            }
            break;
        }
        default: {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
