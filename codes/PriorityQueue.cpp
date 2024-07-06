#include <iostream>
#include <vector>
#include <algorithm>

class PriorityQueue {
private:
    std::vector<int> heap;

public:
    PriorityQueue() {}

    void push(int value) {
        heap.push_back(value);
        std::push_heap(heap.begin(), heap.end());
    }

    void pop() {
        if (!heap.empty()) {
            std::pop_heap(heap.begin(), heap.end());
            heap.pop_back();
        }
    }

    int top() const {
        if (!heap.empty()) {
            return heap.front();
        }
        throw std::runtime_error("PriorityQueue is empty");
    }

    bool empty() const {
        return heap.empty();
    }

    size_t size() const {
        return heap.size();
    }
};

int main() {
    PriorityQueue pq;

    pq.push(10);
    pq.push(20);
    pq.push(5);
    pq.push(30);

    std::cout << "Top element: " << pq.top() << std::endl; // Should print 30

    pq.pop();
    std::cout << "Top element after pop: " << pq.top() << std::endl; // Should print 20

    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    // Should print: 20 10 5

    return 0;
}
