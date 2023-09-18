#include "MyPriorityQueue.hpp"
#include <iostream>

using namespace std;

int main() {
    MyPriorityQueue<int> q;
    q.insert(4);
    q.insert(3);
    q.insert(2);
    q.insert(1);
    q.insert(10);
    q.insert(11);
    q.insert(12);
    q.insert(13);
    q.insert(14);
    q.insert(15);
    q.insert(5);
    q.insert(6);
    q.insert(7);
    q.insert(8);
    q.insert(9);
    q.extractMin();
    q.extractMin();
    q.extractMin();
    

    q.view();

    return 0;
}

// g++ main.cpp -std=c++11 -o p5
