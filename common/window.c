//
// Created by direnol on 11.11.17.
//

#include "../headers/window.h"
WINDOW *init()
{
    if (initscr() == NULL) return NULL;
    if (has_colors() == false) return NULL;
    start_color();
    if (noecho() == ERR) return NULL;
    if (keypad(stdscr, TRUE) == ERR) return NULL;
    signal(SIGWINCH, _resize_term);
    clear();
    box(stdscr, 0, 0);
    if (refresh() == ERR) return NULL;

    return derwin(stdscr, getmaxy(stdscr) - 2, getmaxx(stdscr) - 2, 1, 1);
}
void desturct()
{
    clear();
    refresh();
    endwin();
}

int err_destruct(char *msg)
{
    clear();
    refresh();
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

void refreshTO(WINDOW *w, ...)
{
    va_list ap;
    WINDOW *local = w;
    va_start(ap, w);
    wrefresh(w);
    while (local) {
        wrefresh(local);
        local = va_arg(ap, WINDOW *);
    }
    va_end(ap);

}

size_t rtrim(char *str, size_t len)
{
    size_t new_len = len;
    for (size_t i = len - 1; i >= 0 && str[i] == ' '; --i, --new_len) str[i] = '\0';
    return new_len;
}
void delwinTO(WINDOW *w, ...)
{
    if (w == NULL) return;
    delwin(w);
    va_list ap;
    va_start(ap, w);
    while (w) {
        delwin(w);
        w = va_arg(ap, WINDOW *);
    }
    va_end(ap);
}
curw *tui_new_win(int sy, int sx, int h, int w, char *label, WINDOW *parent)
{
    curw *new = malloc (sizeof *new);
    new->back = derwin(parent, h, w, sy, sx);
    wclear(new->back);
    //Создаем окно для рамки, это уже дочернее окно для фона. Поэтому координаты указываются
    //Относительно родительского окна
    new->decor = derwin(new->back, h - 2, w - 2, 1, 1);
    //Рисуем рамку
    box(new->decor, 0, 0);
    int x, y;
    getmaxyx(new->decor, y, x);
    new->overlay = derwin(new->decor,  y-4, x-2, 1, 1);//рабочее дочернее окно
    wbkgd(new->overlay, COLOR_PAIR(1));
    new->panel = new_panel(new->decor);
    tui_new_label(new->decor, label);
    //Даем команду обновить все это на экране
    update_panels();
    doupdate();
    return new;
}
void tui_new_label(WINDOW *title, char *label)
{
    int pos = (getmaxx(title) / 4);
    if (strlen(label) + pos > getmaxx(title) - pos) {
        mvwprintw(title, 0, pos, "%s", label + (strlen(label) - 2 * pos));
    } else {
        mvwprintw(title, 0, pos, "%s", label);
    }
}
void delcurw(curw *w, ...)
{
    if (w == NULL) return;
    curw *local = w;
    va_list ap;
    va_start(ap, w);
    while (local) {
        del_panel(local->panel);
        delwin(local->overlay);
        delwin(local->decor);
        local = va_arg(ap, curw *);
    }
    va_end(ap);
}
