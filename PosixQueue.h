#ifndef HW1_POSIXQUEUE_H
#define HW1_POSIXQUEUE_H
#include "Node.h"
#include <pthread.h>

class PosixQueue {
private:
    int size;
    Node* start;
    Node* end;
    pthread_mutex_t mutex{};
public:
    PosixQueue();
    ~PosixQueue();
    [[nodiscard]] bool isEmpty() const; // otestuj, zda je fronta prázdná
    [[nodiscard]] int getSize() const;
    void enqueue(int key); // zařaď prvek do fronty (na konec)
    void dequeue(); // vyber prvek z fronty (ze zacatku)
    void printQueue();
};


#endif //HW1_POSIXQUEUE_H
