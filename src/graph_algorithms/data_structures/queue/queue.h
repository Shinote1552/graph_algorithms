#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct queue queue;

queue* queue_create(void);
void queue_delete(queue* q);

void queue_push(queue* q, int value);
void queue_pop(queue* q);
int queue_front(queue* q);
int queue_back(queue* q);
int queue_is_empty(queue* q);
size_t queue_size(queue* q);
void queue_clear(queue* q);

#ifdef __cplusplus
}
#endif

#endif  // S21_QUEUE_H
