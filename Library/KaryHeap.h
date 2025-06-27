#ifndef KARYHEAP_H
#define KARYHEAP_H

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T, typename Compare = std::less<T>>
class KaryHeap {
public:
    // Default constructor
    KaryHeap() : K(2), size(0), capacity(10) {
        root = new T[capacity];
    }

    // Constructor with k value and capacity
    KaryHeap(const int k, const size_t cap, Compare cmp = Compare())
            : K(k), size(0), capacity(cap), cmp(cmp) {
        root = new T[capacity];
    }

    // Constructor de còpia amb capacitat reajustada
    KaryHeap(const KaryHeap& other, const size_t newCapacity)
            : K(other.K), size(other.size), cmp(other.cmp) {
        capacity = newCapacity;
        root = new T[capacity];

        for (size_t i = 0; i < size; ++i) {
            root[i] = other.root[i];
        }
    }

    // Destructor
    ~KaryHeap() {
        delete[] root;
    }

private:
    T *root;
    int K;
    size_t size;
    size_t capacity;
    Compare cmp;

    // Resize the heap array when needed
    void resize() {
        capacity *= 2;
        T *newHeap = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            newHeap[i] = root[i];
        }
        delete[] root;
        root = newHeap;
    }

    // Restore the heap property going downwards
    void restoreDown(size_t index) {
        while (true) {
            size_t max_child_index = SIZE_MAX;
            for (size_t i = 1; i <= K; ++i) {
                size_t child_index = K * index + i;
                if (child_index < size) {
                    if (max_child_index == SIZE_MAX || cmp(root[max_child_index], root[child_index])) {
                        max_child_index = child_index;
                    }
                }
            }

            if (max_child_index == SIZE_MAX) break;
            if (cmp(root[index], root[max_child_index])) {
                swap(root[index], root[max_child_index]);
                index = max_child_index;
            } else break;
        }
    }

    // Restore the heap property going upwards
    void restoreUp(size_t index) {
        while (index > 0) {
            size_t parent = (index - 1) / K;
            if (!cmp(root[parent], root[index])) break;
            swap(root[index], root[parent]);
            index = parent;
        }
    }

public:
    // Insert a new element into the heap
    void insert(T elem) {
        if (size >= capacity) resize();
        root[size] = elem;
        size++;
        restoreUp(size - 1);
    }

    // Extract the maximum element (root) from the heap
    T extractMax() {
        if (size == 0) throw out_of_range("Heap is empty");

        T maxElement = root[0];
        root[0] = root[size - 1];
        size--;
        restoreDown(0);

        return maxElement;
    }

    // Returns the maximum element (root) from the heap without extracting it
    T peek() const {
        if (size == 0) throw std::out_of_range("Heap is empty");
        return root[0];
    }

    // Display the heap elements
    string toString() const {
        if (size == 0) return "";
        stringstream ss;
        ss << root[0];
        for (size_t i = 1; i < size; ++i) {
            ss << ", " << root[i];
        }
        return ss.str();
    }

    // Get the heap as a vector (for returning in ProvaKaryHeap)
    vector<T> getHeapAsVector() {
        vector<T> heapVector;
        for (size_t i = 0; i < size; ++i) {
            heapVector.push_back(root[i]);
        }
        return heapVector;
    }
};

#endif
