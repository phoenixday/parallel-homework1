#include "LockFreeQueue.h"

LockFreeQueue::LockFreeQueue() {
    start = nullptr;
    end = nullptr;
}

bool LockFreeQueue::isEmpty() const {
    return start == nullptr;
}

void LockFreeQueue::enqueue(int key) {
    Node *oldEnd, *newEnd = new Node(key);
    do {
        oldEnd = end.load(std::memory_order_relaxed);
    } while (!end.compare_exchange_weak(oldEnd, newEnd));
    if (isEmpty()) {
        start = newEnd;
    } else {
        oldEnd->next = newEnd;
    }
}

void LockFreeQueue::dequeue() {
    Node *oldStart, *newStart;
    do {
        if (isEmpty()) return;
        oldStart = start.load(std::memory_order_relaxed);
        newStart = oldStart->next;
    } while (!start.compare_exchange_weak(oldStart, newStart));
    delete oldStart;
}