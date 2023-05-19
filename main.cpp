#include <cstdio>
#include <pthread.h>
#include <chrono>
#include "PosixQueue.h"
#include "LockFreeQueue.h"

#define NUM_THREADS 1000

void* testPosixQueue(void *posixQueue) {
    auto* queue = static_cast<PosixQueue*>(posixQueue);

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

    pthread_t threads[NUM_THREADS];

    auto start = std::chrono::steady_clock::now();
    auto* posixQueue = new PosixQueue();

    for (unsigned long & thread : threads) {
        int ret = pthread_create(&thread, nullptr, testPosixQueue, posixQueue);
        if (ret != 0) {
            printf("Error creating thread (´• ω •`) ♡");
        }
    }

    for (unsigned long thread : threads) {
        pthread_join(thread, nullptr);
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> posixDuration = end - start;
    float posixTime = posixDuration.count();

    start = std::chrono::steady_clock::now();
    auto* lockFreeQueue = new LockFreeQueue();

    for (unsigned long & thread : threads) {
        int ret = pthread_create(&thread, nullptr, testLockFreeQueue, lockFreeQueue);
        if (ret != 0) {
            printf("Error creating thread (´• ω •`) ♡");
        }
    }

    for (unsigned long thread: threads) {
        pthread_join(thread, nullptr);
    }

    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> lockFreeDuration = end - start;
    float lockFreeTime = lockFreeDuration.count();

    int percentage = static_cast<int>(lockFreeTime * 100 / posixTime);
    printf("485739\n%d\n", percentage);

    return 0;
}