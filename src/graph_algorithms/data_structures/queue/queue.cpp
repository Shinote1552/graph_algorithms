#include "queue.h"

#include <queue>

/**
 * @brief A structure that represents a queue
 * @param data The data of the queue
 */
struct queue {
  std::queue<int> data;
};

extern "C" {

/**
 * @brief creates a new queue
 * @return a pointer to the new queue
 */
queue* queue_create() { return new queue(); }

/**
 * @brief deletes the queue
 * @return void
 */
void queue_delete(queue* q) { delete q; }

/**
 * @brief adds an element to the queue
 * @return void
 */
void queue_push(queue* q, int value) { q->data.push(value); }

/**
 * @brief removes the first element of the queue
 * @return void
 */
void queue_pop(queue* q) {
  if (!q->data.empty()) {
    q->data.pop();
  }
}

/**
 * @brief returns the first element of the queue
 * @return the first element of the queue or -1 if the queue is empty
 */
int queue_front(queue* q) {
  if (!q->data.empty()) {
    return q->data.front();
  }
  return -1;
}

/**
 * @brief returns the last element of the queue
 * @return the last element of the queue or -1 if the queue is empty
 */
int queue_back(queue* q) {
  if (!q->data.empty()) {
    return q->data.back();
  }
  return -1;  // Возвращаем -1, если очередь пуста
}

/**
 * @brief checks if the queue is empty
 * @return true if the queue is empty, false otherwise
 */
int queue_is_empty(queue* q) { return q->data.empty(); }

/**
 * @brief returns the size of the queue
 * @return the size of the queue
 */
size_t queue_size(queue* q) { return (size_t)q->data.size(); }

/**
 * @brief clears the queue
 * @return void
 */
void queue_clear(queue* q) {
  while (!q->data.empty()) {
    q->data.pop();
  }
}

}  // extern "C"
