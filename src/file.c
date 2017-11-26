//
// Created by direnol on 12.11.17.
//

#include "../headers/file.h"
int open_file(char *name, int *fd, const int *param)
{
    int p;
    if (param == NULL) p = O_RDWR;
    else p = *param;
    *fd = open(name, p);
    if (*fd != (-1)) return EXIT_SUCCESS;
    *fd = open(name, O_CREAT, 0666);
    if (*fd < 0) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

long size_of_file(int file, long *n)
{
    if (file < 0) return EXIT_FAILURE;
    long cur = lseek(file, 0L, SEEK_CUR);
    if (cur < 0) return EXIT_FAILURE;
    *n = lseek(file, 0L, SEEK_END);
    if (*n < 0) return EXIT_FAILURE;
    if (lseek(file, cur, SEEK_SET) < 0) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
int read_file(int file, char *buf, long start, long count)
{
    if (file < 0) return EXIT_FAILURE;
    long size;
    if (size_of_file(file, &size)) return EXIT_FAILURE;
    if (start < 0) return EXIT_FAILURE;
    lseek(file, start, SEEK_SET);
    ssize_t n;
    n = read(file, buf, (size_t) count);
    if (n <= 0) return EXIT_FAILURE;
    buf[n] = '\0';
    return EXIT_SUCCESS;
}
int close_file(int *fd)
{
    if (*fd < 0) return EXIT_FAILURE;
    close(*fd);
    *fd = -1;
    return EXIT_SUCCESS;
}



