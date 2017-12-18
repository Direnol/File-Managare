
#include <stdlib.h>
#include "../headers/manager.h"

int main(int argc, char **argv)
{
    WINDOW *w = NULL;
    WINDOW **wins = malloc(2 * sizeof(WINDOW *));
    if (initscr() == NULL) {
        return err_destruct("Init");
    }
    if ((w = init()) == NULL) {
        endwin();
        exit(1);
    }
    WINDOW **boxes = malloc(2 * sizeof(WINDOW *));
    init_pair(1, COLOR_WHITE, COLOR_MAGENTA);
    if (create_win_manager(w, wins, boxes)) {
        endwin();
        exit(1);
    }

    DIR *dir = NULL;
    char *path[2];
    path[0] = malloc(256 * sizeof(char));
    path[1] = malloc(256 * sizeof(char));
    struct dirent **list = NULL;
    getcwd(path[0], 256);
    getcwd(path[1], 256);
    scrollok(wins[0], TRUE);
    scrollok(wins[1], TRUE);

    bool cur_window = 0;
    int y[2] = {0, 0};
    chtype c;
    bool work = 1;
    int x, n;
    n = scandir(path[cur_window], &list, 0, alphasort);
    show_manager(wins[1], y[1], list, n, boxes[1], path[1]);
    WINDOW *status = newwin(4, 4, getmaxy(stdscr) / 2, getmaxx(stdscr) / 2);
    box(status, 0, 0);
    PANEL *pan1 = new_panel(status);
    while (work) {
        wrefresh(wins[cur_window]);
        show_manager(wins[cur_window], y[cur_window], list, n, boxes[cur_window], path[cur_window]);

        switch (c = (chtype) getch()) {
            case KEY_F(1): {
                show_panel(pan1);
                doupdate();
                break;
            }
            case KEY_F(2): {
                hide_panel(pan1);
                update_panels();
                doupdate();
                break;
            }
            case KEY_F(5): {
                cp(list[y[cur_window]]->d_name, path[cur_window ^ 1]);
                break;
            }
            case KEY_F(10): {
                work = 0;
                break;
            }
            case KEY_DOWN:
            case KEY_UP: {
                key_map(wins[cur_window], c, n - 1);
                getyx(wins[cur_window], y[cur_window], x);
                break;
            }
            case KEY_LEFT:wscrl(wins[cur_window], -1);
                wrefresh(wins[cur_window]);
                getch();
            case KEY_RIGHT:wscrl(wins[cur_window], 1);
                wrefresh(wins[cur_window]);
                getch();
                break;
            case '\t': {
                cur_window ^= 1;
                chdir(path[cur_window]);
                free(list);
                list = NULL;
                n = scandir(path[cur_window], &list, 0, alphasort);
                break;
            }
            case '\n':
                if (isDir(list[y[cur_window]])) {
                    chdir(path[cur_window]);
                    strcpy(path[cur_window], list[y[cur_window]]->d_name);
                    openDir(&dir, &path[cur_window]);
                    free(list);
                    list = NULL;
                    y[cur_window] = 0;
                    n = scandir(path[cur_window], &list, 0, alphasort);
                    break;
                } else {
                    pid_t editor;
                    if ((editor = fork()) == 0) {
                        execl(PATH_EDITOR, EDITOR, list[y[cur_window]]->d_name, NULL);
                        endwin();
                        exit(EXIT_FAILURE);
                    } else if (editor < 0) {
                        endwin();
                        exit(EXIT_FAILURE);
                    }
                    wait(NULL);
                }
            case KEY_RESIZE: {
                delwinTO(w, boxes[0], boxes[1], wins[0], wins[1]);
                clear();
                if ((w = init()) == NULL) {
                    endwin();
                    exit(1);
                }
                if (create_win_manager(w, wins, boxes)) {
                    endwin();
                    exit(1);
                }
                show_manager(wins[cur_window], y[cur_window], list, n, boxes[cur_window], path[cur_window]);
                show_manager(wins[cur_window ^ 1],
                             y[cur_window ^ 1],
                             list,
                             n,
                             boxes[cur_window ^ 1],
                             path[cur_window ^ 1]);
                refreshTO(wins[0], wins[1], NULL);
            }
            default:break;
        }
    }

    if (list) free(list);
    free(path[0]);
    free(path[1]);
    closedir(dir);
    delwinTO(wins[0], wins[1], boxes[0], boxes[1], status, w, NULL);
    free(boxes);
    free(wins);
    desturct();
    return 0;
}