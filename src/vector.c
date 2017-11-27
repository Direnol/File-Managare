#include "../headers/vector.h"

struct vector *create_vector(size_t nmemb, size_t size)
{
    struct vector *head = malloc(sizeof(*head));
    if (!head) {
        return NULL;
    }
    if (nmemb < 1) {
        nmemb = 1;
    }

    head->nmemb = 0;
    head->_allocated = nmemb;
    head->size = size;
    head->memory = malloc(size * nmemb);
    if (!head->memory) {
        free(head);
        return NULL;
    }
    return head;
}

void *get_vector(struct vector *head, size_t ind)
{
    if (head == NULL) return NULL;
    char *ptr = head->memory;
    if (ind > head->nmemb) return NULL;

    ptr = ptr + (ind * head->size);
    return ptr;
}

void *push_vector(struct vector *head, void *data)
{
    if (head == NULL) return NULL;
    if (head->nmemb == head->_allocated) {
        head->_allocated *= 2;
        head->memory = realloc(head->memory, head->_allocated * head->size);
        if (head->memory == NULL) {
            return NULL;
        }
    }
    char *ptr = head->memory + (head->nmemb * head->size);
    if (memcpy(ptr, data, head->size) == NULL) {
        return NULL;
    }
    ++head->nmemb;
    return ptr;
}


int pop_vector(struct vector *head, size_t ind)
{
    if (head == NULL || ind > head->nmemb || head->nmemb == 0) {
        return EXIT_FAILURE;
    }
    --head->nmemb;
    if (head->_allocated - 1 == ind) {
        return EXIT_SUCCESS;
    }
    char *p1 = head->memory + (ind * head->size);
    char *p2 = head->memory + ((ind + 1) * head->size);
    if (memmove(p1, p2, (head->_allocated - ind) * head->size) == NULL) {
        return EXIT_FAILURE;
    }
    if (head->_allocated % head->nmemb == 0) {
        head->memory = realloc(head->memory, head->nmemb * head->size);
        head->_allocated = head->nmemb;
        if (head->memory == NULL) {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}


int free_vector(struct vector **head)
{
    if (*head == NULL) return EXIT_FAILURE;
    free((*head)->memory);
    free(*head);
    *head = NULL;
    return EXIT_SUCCESS;
}

size_t size_vector(struct vector *head)
{
    if (head == NULL) return 0;
    return head->nmemb;
}

int change_vector(struct vector *head, size_t ind, void *data)
{
    if (ind > size_vector(head) || head == NULL) {
        return EXIT_FAILURE;
    }
    char *p = head->memory + (ind * head->size);
    memmove(p, data, head->size);
    return EXIT_SUCCESS;
}