//
// Created by direnol on 11.11.17.
//

#include <stdio.h>
#include "../headers/editor.h"
int main(int argc, char **argv)
{

    PANEL *enter = NULL;
    if (init(enter)) {
        return err_destruct("init");
    }
    WINDOW *win = newwin(getmaxy(stdscr) - 4, getmaxx(stdscr) - 2, 1, 1);
    if (!win) return err_destruct("Create window");
    bool work = true;
    char *buffer = malloc(sizeof(char) * getmaxx(win) + 1);
    if (!buffer) return err_destruct("Malloc");
    chtype c;
    int file = -1;
    int max_pos = 0;
    int cur = 0;
    while (work) {
        wrefresh(win);
        c = (chtype) getch();
        switch (c) {
            case (KEY_F(1)): {
                wclear(win);
                waddstr(win, "Enter filename: ");
                echo();
                wgetstr(win, buffer);
                noecho();
                wclear(win);
                openF1(win, &file, &cur, &max_pos, buffer);
                break;
            }
            case (KEY_F(2)): {
                saveF2(win, file, max_pos, buffer);
                break;
            }
            case (KEY_F(3)): {
                close_file(&file);
                work = false;
                break;
            }
            default: {
                keymap(win, c, &cur, &max_pos);
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