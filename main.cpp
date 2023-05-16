#include <cstdio>
#include <pthread.h>
#include <chrono>
#include "PosixQueue.h"
#include "LockFreeQueue.h"

#define NUM_THREADS 10000

void* testPosixQueue(void *posixQueue) {
    auto* queue = static_cast<PosixQueue*>(posixQueue);

    for (int j = 0; j < 50; j++) {
        for (int i = 0; i < 10; i++) {
            queue->enqueue(i);
        }

        for (int i = 0; i < 5; i++) {
            queue->dequeue();
        }
    }

    return nullptr;
}

void* testLockFreeQueue(void *lockFreeQueue) {
    auto* queue = static_cast<LockFreeQueue*>(lockFreeQueue);

    for (int j = 0; j < 100; j++) {
        for (int i = 0; i < 10; i++) {
            queue->enqueue(i);
        }

        for (int i = 0; i < 5; i++) {
            queue->dequeue();
        }
    }

    return nullptr;
}

int main() {

    printf("485739\n");

    pthread_t threads[NUM_THREADS];

//    auto start = std::chrono::steady_clock::now();
//    auto* posixQueue = new PosixQueue();
//
//    for (int t = 0; t < NUM_THREADS; t++) {
//        int ret = pthread_create(&threads[t], nullptr, testPosixQueue, posixQueue);
//        if (ret != 0) {
//            printf("Error creating thread (´• ω •`) ♡");
//        }
//    }
//
//    for (unsigned long thread : threads) {
//        pthread_join(thread, nullptr);
//    }
//
//    auto end = std::chrono::steady_clock::now();
//    std::chrono::duration<double> elapsed_seconds = end-start;
//    printf("Duration (posix): %f seconds\n", elapsed_seconds.count());
//    posixQueue->getSize();

    auto start = std::chrono::steady_clock::now();
    auto* lockFreeQueue = new LockFreeQueue();

    for (int t = 0; t < NUM_THREADS; t++) {
        int ret = pthread_create(&threads[t], nullptr, testLockFreeQueue, lockFreeQueue);
        if (ret != 0) {
            printf("Error creating thread (´• ω •`) ♡");
        }
    }

    for (unsigned long thread: threads) {
        pthread_join(thread, nullptr);
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    printf("Duration (lock-free): %f seconds\n", elapsed_seconds.count());
    lockFreeQueue->getSize();

    return 0;
}