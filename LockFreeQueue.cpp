#include "LockFreeQueue.h"
#include <cstdio>

// https://blog.devgenius.io/a-simple-guide-to-atomics-in-c-670fc4842c8b

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

int LockFreeQueue::getSize() const {
    int size = 0;
    Node* curr = start;
    while (curr != nullptr) {
        size += 1;
        curr = curr->next;
    }
    printf("size: %d (◕‿◕)♡\n", size);
    return size;
}

void LockFreeQueue::printQueue() {
    if (isEmpty()) {
        printf("empty queue ( ˘⌣˘)♡(˘⌣˘ )\n");
        return;
    }
    int size = 0;
    Node* curr = start;
    while (curr != nullptr) {
        printf("%d ", curr->key);
        size += 1;
        curr = curr->next;
    }
    printf("\nsize: %d (◕‿◕)♡\n", size);
}
