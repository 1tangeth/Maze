#include <iostream>

#include "cs221util/catch.hpp"
#include "queue.h"
#include "stack.h"
using namespace std;

TEST_CASE("stack::basic functions", "[weight=1][part=stack]") {
    // cout << "Testing Stack..." << endl;
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.push(i);
    }
    while (!intStack.isEmpty()) {
        result.push_back(intStack.pop());
    }
    REQUIRE(result == expected);
}

TEST_CASE("queue::basic functions", "[weight=1][part=queue]") {
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    // {1,2,3,4,5,6,7,8,9,10}
    for (int i = 1; i <= 10; i++) {
        intQueue.enqueue(i);
    }
    
    intQueue.dequeue();
    intQueue.dequeue();
    intQueue.dequeue();
    intQueue.dequeue();
    
    REQUIRE(intQueue.peek() == 1);
}