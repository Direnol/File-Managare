#ifndef FILE_MANAGARE_VECTOR_H
#define FILE_MANAGARE_VECTOR_H

#include <stdlib.h>
#include <memory.h>

struct vector {
    void *memory;
    // sizeof(data)
    size_t size;
    // number of data
    size_t nmemb;
    // number of allocated memory(bytes)
    size_t _allocated;
};

struct vector *create_vector(size_t nmemb, size_t size);

void *get_vector(struct vector *head, size_t ind);

void *push_vector(struct vector *head, void *data);

int free_vector(struct vector **head);

int pop_vector(struct vector *head, size_t ind);

size_t size_vector(struct vector *head);

int change_vector(struct vector *head, size_t ind, void *data);

#endif //FILE_MANAGARE_VECTOR_H
