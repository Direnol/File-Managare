//
// Created by direnol on 11.11.17.
//

#include "window.h"
int main(int argc, char **argv)
{
    PANEL *enter = NULL;
    if (init(enter)) {
        return err_destruct("init");
    }
    WINDOW *win = newwin(getmaxy(stdscr) - 4, getmaxx(stdscr) - 2, 1, 1);
    if (!win) return err_destruct("Create window");
    bool work = true;
    char *buffer = malloc(sizeof(char) * getmaxy(win));
    if (!buffer) return err_destruct("Malloc");
    chtype c;
    int x, y;
    while (work) {
        getyx(win, y, x);
        wrefresh(win);
        c = (chtype) getch();
        switch (c) {
            case (KEY_UP):
            case (KEY_LEFT):
            case (KEY_DOWN):
            case (KEY_RIGHT): {
                movexy(c, win);
                break;
            }
            case (127): {
                wdelch(win);
                break;
            }
            case (KEY_DC): {
                wdelch(win);
                break;
            }
            case (KEY_F(5)): {
                wclear(win);
                echo();
                wgetstr(win, buffer);
                noecho();
                wclear(win);
                waddstr(win, buffer);
                break;
            }
            case (KEY_F(3)): {
                work = false;
                break;
            }
            case (KEY_F(6)): {
                winnstr(win, buffer, 5);
                break;
            }
            case (KEY_F(7)): {
                waddstr(win, buffer);
                break;
            }
            default: {
                waddch(win, c);
                break;
            }
        }
    }
    refresh();
    delwin(win);
    desturct();
    //mvwinnstr()
    return EXIT_SUCCESS;
}