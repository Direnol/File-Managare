#include "../headers/editor.h"

int keymap(WINDOW *win, chtype key, int *cur, int *max)
{
    if (win == NULL) return EXIT_FAILURE;

    switch (key) {
        case (KEY_UP):
        case (KEY_LEFT):
        case (KEY_DOWN):
        case (KEY_RIGHT): {
            movexy(key, win, cur, max);
            break;
        }
        case (127): {
            if (*cur == 0)
                return EXIT_FAILURE;
            movexy(KEY_LEFT, win, cur, max);
            wdelch(win);
            --(*max);
            break;
        }
        case (KEY_DC): {
            if (*cur == *max)
                return EXIT_FAILURE;
            wdelch(win);
            --(*max);
            break;
        }
        case ('\n'): {
            int x, y, mx, my;
            getyx(win, y, x);
            getmaxyx(win, my, mx);
            if (y == my) {
                return EXIT_FAILURE;
            }
            *cur += (mx - x);
            *max = *cur;
            waddch(win, '\n');
            break;
        }
        default: {
            if (*cur == *max) {
                ++(*max);
            }
            ++(*cur);

            waddch(win, key);
            break;
        }
    }

    return EXIT_SUCCESS;
}

int saveF2(WINDOW *win, int fd, int max_pos, char *name)
{
    if (!win || fd < 0 || max_pos < 0) return EXIT_FAILURE;
    int my, mx;
    getmaxyx(win, my, mx);
    char *buf = calloc((size_t) (mx + 2), sizeof(char));
    if (!buf) return EXIT_FAILURE;
    if (close_file(&fd)) {
        return EXIT_FAILURE;
    }
    int param = O_WRONLY | O_TRUNC;
    open_file(name, &fd, &param);
    int yy = max_pos / mx;
    for (int i = 0; i <= yy && i < my; ++i) {
        memset(buf, 0, (size_t) (mx + 2));
        mvwinnstr(win, i, 0, buf, mx);
        ltrim(buf, strlen(buf));
        size_t n = strlen(buf);
        buf[n] = '\n';
        buf[n + 1] = '\0';
        write(fd, buf, n + 1);
    }

    close_file(&fd);
    free(buf);
    return EXIT_SUCCESS;
}
void ltrim(char *str, size_t len)
{
    for (size_t i = len - 1; i >= 0 && str[i] == ' '; --i) str[i] = '\0';
}
int openF1(WINDOW *win, int *file, int *cur, int *max, char *buffer)
{
    close_file(file);
    if (open_file(buffer, file, NULL)) {
        wprintw(win, "cannot open %s", buffer);
        wgetch(win);
        wclear(win);
        return EXIT_FAILURE;
    }
    char *buf = malloc(sizeof(char) * getmaxx(win));
    long n;
    size_of_file(*file, &n);
    wclear(win);
    for (int i = 0; i < n; i += getmaxx(win)) {
        if (read_file(*file, buf, i, getmaxx(win))) {
            waddstr(win, buf);
            break;
        }
        waddstr(win, buf);
    }
    free(buf);
    *max = (int) n;
    *cur = 0;
    wmove(win, 0, 0);
    return EXIT_SUCCESS;
}
int ctrl(WINDOW *win, int *cur, int *max)
{
    chtype c;
    c = (chtype) wgetch(win);

    // switch

    return EXIT_SUCCESS;
}
