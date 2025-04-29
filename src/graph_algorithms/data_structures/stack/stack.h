#ifndef S21_STACK_H
#define S21_STACK_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct stack stack;

stack* stack_create(void);
void stack_delete(stack* s);

void stack_push(stack* s, int value);
void stack_pop(stack* s);
int stack_top(stack* s);
bool stack_is_empty(stack* s);
void stack_clear(stack* s);
size_t stack_size(stack* s);
void stack_swap(stack* s1, stack* s2);

#ifdef __cplusplus
}
#endif

#endif  // S21_STACK_H
