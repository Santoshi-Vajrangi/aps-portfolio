#include <iostream>
#include <stdexcept>

class DynamicArray {
private:
    int* data;
    size_t size;
    size_t capacity;

    void resize(size_t new_capacity) {
        int* new_data = new int[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    DynamicArray() : data(nullptr), size(0), capacity(0) {}

    ~DynamicArray() {
        delete[] data;
    }

    void push_back(int value) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    void pop_back() {
        if (size > 0) {
            --size;
        }
    }

    int at(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t get_size() const {
        return size;
    }

    size_t get_capacity() const {
        return capacity;
    }

    bool empty() const {
        return size == 0;
    }

    void display() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    DynamicArray arr;

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    std::cout << "Array elements: ";
    arr.display();

    std::cout << "Element at index 1: " << arr.at(1) << std::endl;

    arr.pop_back();
    std::cout << "Array after pop_back: ";
    arr.display();

    std::cout << "Size: " << arr.get_size() << std::endl;
    std::cout << "Capacity: " << arr.get_capacity() << std::endl;

    return 0;
}
