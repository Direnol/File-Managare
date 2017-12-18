//
// Created by direnol on 11.11.17.
//

#include <stdio.h>
#include "../headers/editor.h"
int main(int argc, char **argv)
{
    WINDOW *overlay = NULL;
    if ((overlay = init()) == NULL) {
        return err_destruct("init");
    }
    WINDOW *win = NULL;
    win = derwin(overlay, getmaxy(overlay) - 2, getmaxx(overlay) - 2, 1, 1);


    bool work = true;
    char *buffer = malloc(sizeof(char) * getmaxx(win) + 1);
    if (!buffer) return err_destruct("Malloc");
    chtype c;
    int file = -1;
    int max_pos = 0;
    int cur = 0;

    if (openF1(win, &file, &cur, &max_pos, argv[1])) {
        return err_destruct("Open");
    }

    while (work) {
        wrefresh(win);
        c = (chtype) getch();
        switch (c) {
            case (KEY_F(2)): {
                if (saveF2(win, file, max_pos, buffer)) {
                    return err_destruct("Save");
                }
                wclear(win);
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