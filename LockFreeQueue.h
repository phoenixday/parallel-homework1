#ifndef HW1_LOCKFREEQUEUE_H
#define HW1_LOCKFREEQUEUE_H
#include "Node.h"
#include <atomic>

class LockFreeQueue {
private:
    std::atomic<Node*> start{};
    std::atomic<Node*> end{};
public:
    LockFreeQueue();
    [[nodiscard]] bool isEmpty() const; // otestuj, zda je fronta prázdná
    void enqueue(int key); // zařaď prvek do fronty (na konec)
    void dequeue(); // vyber prvek z fronty (ze zacatku)
};


#endif //HW1_LOCKFREEQUEUE_H
