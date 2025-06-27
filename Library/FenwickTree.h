#ifndef UTILS_FENWICKTREE_H
#define UTILS_FENWICKTREE_H

#include <bits/stdc++.h>
using namespace std;

template<typename T = int>
class FenwickTree {

public:
    /**
     * Default constructor
     */
    FenwickTree() : array(nullptr) {}

    /**
     * Constructor from the array
     */
    FenwickTree(T data[], size_t n, T neutre) {
        // Create the array to store tree's data
        length = n;
        array = new T [length + 1];
        original = new T [length];

        // Initialize the array
        for(int i = 0; i <= length; i++) array[i] = neutre;

        // Store the introduced data values using the update function
        for (size_t i = 1; i <= length; ++i) {
            original[i - 1] = data[i - 1];
            array[i] += original[i - 1];
            size_t j = i + (i & -i);
            if (j <= length) {
                array[j] += array[i];
            }
        }
    }

private:
    /**
     * Pointer to the data array of the tree
     */
    T *array, *original;

    /**
     * Length of the tree's array
     */
    size_t length;

public:
    /**
     * Public method to get the sum until the selected index
     * @param index Index from the array
     * @return Value of the sum until the selected index
     */
    T getSum(size_t index) {
        T result = 0;
        while (index > 0) {
            result += array[index];
            index -= index & (-index);
        }
        return result;
    }

    /**
     * Public method to do the sum of the values between the two selected indexes
     * @param from Index from the array
     * @param to Index from the array
     * @return Value of the sum between inserted indexes
     */
    T getSum(size_t from, size_t to) {
        if (from > to) return 0;
        return getSum(to + 1) - getSum(from);
    }

    /**
     * Public method to change the value of a certain position of used array
     * @param index Target index to update
     * @param newValue Value to set in the position
     */
    void updateBIT(size_t index, T newValue) {
        if (index < 0 || index >= length) return;
        T delta = newValue - original[index];
        original[index] = newValue;
        updateBITAux(index + 1, delta);
    }

    string toString() const {
        ostringstream oss;
        oss << "FenwickTree internal array (1-based indexing):\n";
        for (size_t i = 1; i <= length; ++i) {
            oss << '\t' << "[" << i << "] = " << array[i] << "\n";
        }
        oss << "Original array (0-based indexing):\n";
        for (size_t i = 0; i < length; ++i) {
            oss << '\t' << "[" << i << "] = " << original[i] << "\n";
        }
        return oss.str();
    }

private:
    /**
     * Private method to insert the values into the tree
     * @param index Index of the tree where the value has to be inserted
     * @param value Value being insert into the tree
     */
    void updateBITAux(size_t index, T value) {
        while (index <= length) {
            array[index] += value;
            index += index & (-index);
        }
    }
};

#endif //UTILS_FENWICKTREE_H
