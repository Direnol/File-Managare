//
// Created by direnol on 12.11.17.
//

#include "file.h"
int open_file(char *name)
{
    int res = open(name, O_RDWR);
    if (res != (-1)) return EXIT_SUCCESS;
    res = open(name, O_CREAT, 0666);
    if (res < 0) return EXIT_FAILURE;
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
    if (start < 0 || (count - start) > size) return EXIT_FAILURE;
    lseek(file, start, SEEK_SET);
    if (read(file, buf, (size_t) count) == 0) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}



