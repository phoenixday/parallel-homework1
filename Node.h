#ifndef HW1_NODE_H
#define HW1_NODE_H

struct Node {
    int key;
    Node* next;

    explicit Node(int keyVal) {
        key = keyVal;
        next = nullptr;
    }
};

#endif //HW1_NODE_H
