#include "PosixQueue.h"
#include <pthread.h>

PosixQueue::PosixQueue() {
    size = 0;
    start = nullptr;
    end = nullptr;

    pthread_mutex_init(&mutex, nullptr);
}

PosixQueue::~PosixQueue() {
    pthread_mutex_destroy(&mutex);
}

bool PosixQueue::isEmpty() const {
    return size == 0;
}

void PosixQueue::enqueue(int key) {
    pthread_mutex_lock(&mutex);
    if (isEmpty()) {
        start = new Node(key);
        end = start;
        size = 1;
    } else {
        Node *node = new Node(key);
        end->next = node;
        end = node;
        size++;
    }
    pthread_mutex_unlock(&mutex);
}

void PosixQueue::dequeue() {
    if (isEmpty()) return;
    pthread_mutex_lock(&mutex);
    if (size == 1) {
        delete start;
        start = nullptr;
        end = nullptr;
        size = 0;
    } else {
        Node *newStart = start->next;
        delete start;
        start = newStart;
        size--;
    }
    pthread_mutex_unlock(&mutex);
}

