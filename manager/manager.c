#include "../headers/manager.h"


int openDir(DIR **dir, char **path)
{
    if (dir == NULL || path == NULL) return EXIT_FAILURE;
    if (*path == NULL) {
        *path = getcwd(NULL, BUF_SIZE);
        if (*path == NULL) return EXIT_FAILURE;
    }

    if (*dir != NULL) {
        closedir(*dir);
    }
    *dir = opendir(*path);
    if (*dir == NULL) return EXIT_FAILURE;
    if (chdir(*path) < 0) return EXIT_FAILURE;
    getcwd(*path, 256);

    return EXIT_SUCCESS;
}
int compareDir(void *a, void *b)
{
    char *aa = (char *) (a);
    struct dirent *bb = *(struct dirent **) (b);
//    printf("[%s] ? [%s]\n", aa, bb->d_name);
    return strcmp(aa, bb->d_name);
}
int create_win_manager(WINDOW *parent, WINDOW **win, WINDOW **boxes)
{
    int x = 0, y = 0;
    getmaxyx(parent, y, x);
    boxes[0] = derwin(parent, y - 2, x / 2 - 1, 1, 1);
    boxes[1] = derwin(parent, y - 2, x / 2 - 1, 1, x / 2 + 1);
    if (!boxes[0] || !boxes[1]) return EXIT_FAILURE;
    win[0] = derwin(boxes[0], getmaxy(boxes[0]) - 2, getmaxx(boxes[0]) - 2, 1, 1);
    win[1] = derwin(boxes[1], getmaxy(boxes[1]) - 2, getmaxx(boxes[1]) - 2, 1, 1);
    if (!win[0] || !win[1]) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void show_manager(WINDOW *w, int y, struct dirent **dir, int n, WINDOW *b, char *cur_dir)
{
    wclear(w);
    box(b, 0, 0);
    int pos = (getmaxx(b) / 4);
    if (strlen(cur_dir) + pos > getmaxx(b) - pos) {
        mvwprintw(b, 0, pos, "...%s", cur_dir + (strlen(cur_dir) - 2 * pos));
    } else {
        mvwprintw(b, 0, pos, "%s", cur_dir);
    }

    struct stat st;
    wrefresh(b);
    if (dir != NULL) {
        for (int i = 0; i < n; ++i) {
            stat(dir[i]->d_name, &st);
            if (y != i) {
                mvwprintw(w, i, 0, "%c%s",  (dir[i]->d_type == DT_DIR ? '/' : ' '), dir[i]->d_name, st.st_size);
                if (dir[i]->d_type != DT_DIR) {
                    wprintw(w, "[%d]", st.st_size);
                }
            } else {
                wattron(w, COLOR_PAIR(1));
                mvwprintw(w, i, 0, "%c%s", (dir[i]->d_type == DT_DIR ? '/' : ' '), dir[i]->d_name, st.st_size);
                if (dir[i]->d_type != DT_DIR) {
                    wprintw(w, "[%d]", st.st_size);
                }
                wattroff(w, COLOR_PAIR(1));
            }
        }
    }
    wmove(w, y, 0);
    wrefresh(w);
}
void key_map(WINDOW *win, chtype c, int my)
{
    int x, y;
    getyx(win, y, x);
    switch (c) {
        case KEY_UP:
            if (y == 0) {
                break;
            }
            wmove(win, y - 1, x);
            break;
        case KEY_DOWN:
            if (y == my) {
                break;
            }
            wmove(win, y + 1, x);
            break;
        default:break;

    }
}

bool isDir(struct dirent *file)
{
    if (file->d_type == DT_DIR) return true;
    return false;
}

void cp(char *file, char *to_path)
{
    int fd = open(file, O_RDONLY);
    if (fd < 0) {
        int er = errno;
        clear();
        endwin();
        errno = er;
        perror("Src file:");
        exit(er);
    }
    char *to_file = malloc(sizeof(char) * (strlen(file) + strlen(to_path) + 2));
    sprintf(to_file, "%s/%s", to_path, file);
    int to_fd =  creat(to_file, 0666);
    if (to_fd < 0) {
        int er = errno;
        clear();
        endwin();
        errno = er;
        perror("Dest file:");
        exit(er);
    }
    pthread_t copy;
    int arg[2] = {fd, to_fd};
    struct stat st;
    if (stat(file, &st) < 0) {
        perror("Stat copy file:");
        exit(errno);
    }
    __off_t all_size = st.st_size;
    __off_t cur_size = 0;

    pthread_create(&copy, NULL, _cp, arg);
    WINDOW *lwin = init_load_percent();
    do {
        stat(to_file, &st);
        cur_size = st.st_size;
        load_percent(lwin, cur_size + 1, all_size + 1);
        sleep(1);
    } while (cur_size != all_size);
    pthread_join(copy, NULL);
    del_load_percent(lwin);
    close(fd);
    close(to_fd);
    free(to_file);
}

void *_cp(void *argv)
{
    int fd = ((int *) argv)[0];
    int to_fd = ((int *) argv)[1];

    void *buf = malloc(BUF_SIZE);
    size_t n = 0;
    while ((n = (size_t) read(fd, buf, BUF_SIZE)) != 0) {
        write(to_fd, buf, n);
    }
    return NULL;
}

WINDOW *init_load_percent()
{
    WINDOW *win = newwin(1, getmaxx(stdscr) - 2, getmaxy(stdscr) - 2, 1);
    return win;
}

void del_load_percent(WINDOW *win)
{
    getch();
    wclear(win);
    wrefresh(win);
    delwin(win);
}

void load_percent(WINDOW *win, __off_t cur, __off_t all)
{
    wclear(win);
    int max = getmaxx(win);
    int percent = (int) ((cur * max) / all);
    for (int i = 0; i < percent; ++i) {
        mvwaddch(win, 0, i, ACS_BLOCK);
    }
    wrefresh(win);
}
