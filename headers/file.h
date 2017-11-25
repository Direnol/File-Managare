//
// Created by direnol on 12.11.17.
//

#ifndef FILE_MANAGARE_FILE_H
#define FILE_MANAGARE_FILE_H

#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

int open_file(char *name, int *fd, int *param);

int read_file(int file, char *buf, long start, long count);

long size_of_file(int file, long *n);

int close_file(int *fd);

#endif //FILE_MANAGARE_FILE_H
