#include "stack.h"

#include <stack>

/**
 * @brief A structure that represents a stack
 * @param data The data of the stack
 */
struct stack {
  std::stack<int> data;
};

extern "C" {

/**
 * @brief creates a new stack
 * @return a pointer to the new stack
 */
stack* stack_create() { return new stack(); }

/**
 * @brief deletes the stack
 * @return void
 */
void stack_delete(stack* s) { delete s; }

/**
 * @brief adds an element to the stack
 * @return void
 */
void stack_push(stack* s, int value) { s->data.push(value); }

/**
 * @brief removes the top element of the stack
 * @return void
 */
void stack_pop(stack* s) {
  if (!s->data.empty()) {
    s->data.pop();
  }
}

/**
 * @brief returns the top element of the stack
 * @return the top element of the stack or -1 if the stack is empty
 */
int stack_top(stack* s) {
  if (!s->data.empty()) {
    return s->data.top();
  }
  return -1;
}

/**
 * @brief checks if the stack is empty
 * @return true if the stack is empty, false otherwise
 */
bool stack_is_empty(stack* s) { return s->data.empty(); }

/**
 * @brief returns the size of the stack
 * @return the size of the stack (size_t type)
 */
size_t stack_size(stack* s) { return s->data.size(); }

/**
 * @brief clears the stack
 * @return void
 */
void stack_clear(stack* s) {
  while (!s->data.empty()) {
    s->data.pop();
  }
}

/**
 * @brief swaps the contents of two stacks
 * @return void
 */
void stack_swap(stack* s1, stack* s2) { s1->data.swap(s2->data); }

}  // extern "C"
