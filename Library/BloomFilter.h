#ifndef UTILS_BLOOMFILTER_H
#define UTILS_BLOOMFILTER_H

#include <bits/stdc++.h>
using namespace std;

/**
 * Bloom filter main class
 * @tparam T Type of the data
 * @tparam N Number of elements
 * @tparam M Bitmap size
 * @tparam K Number of hash functions
 * @tparam Hash Custom function of hash code generator for selected type
 */
template <typename T, size_t N, size_t M, size_t K, vector<size_t> (*Hash)(const T&) = nullptr>
class BloomFilter {
public:
    /**
     * Main constructor
     */
    BloomFilter () {
        // Validate that N, K, and M are greater than 0
        if (!N || !K || !M) {
            throw invalid_argument("N, K, and M must be greater than 0");
        }

        // If a custom hash function is provided, validate that it generates exactly K elements
        if (Hash == nullptr) {
            // Check if the default std::hash<T> can be used for the type T
            if (!is_invocable_r_v<size_t, hash<T>, T>) {
                throw invalid_argument("Selected type is not hashable");
            }
        }
    }

private:
    // Array of bits
    bitset<M> bits;

    /**
     * Default hash code generator which uses multiple hash iterations
     * @param data to convert to hash codes
     * @return vector of hash codes
     */
    vector<size_t> hashFunction(const T& data) const {
        vector<size_t> values(K);
        hash<T> hash_fn;
        for (size_t i = 0; i < K; ++i) {
            values[i] = (hash_fn(data) * (i + 1)) % M;
        }
        return values;
    }

public:
    /**
     * Inserts the data into the bloom filter
     * @param data to insert into the Bloom Filter
     */
    void insert(const T& data) {
        vector<size_t> values;
        if (Hash != nullptr) {
            values = Hash(data);
            //printf("%d %d\n", values.size(), K);
            if (values.size() != K) {
                throw runtime_error("Number of elements generated with custom hash function does not match provided value: "
                + to_string(values.size()) + " instead of " + to_string(K));
            }
        } else {
            values = hashFunction(data);
        }
        for (size_t i = 0; i < K; ++i) {
            bits.set(values[i]);
        }
    }

    /**
     * Checks if the data might be in the bloom filter
     * @return if the value is inside the Bloom filter
     */
    bool contains(const T& data) const {
        vector<size_t> values;
        if (Hash != nullptr) {
            values = Hash(data);
        } else {
            values = hashFunction(data);
        }

        for (size_t i = 0; i < K; ++i) {
            if (!bits.test(values[i])) {
                return false;
            }
        }
        return true;
    }

    /**
     * Calculates the false positive probability
     * @return The probability of getting a false positive
     */
    [[nodiscard]] double falsePositive() const {
        return pow((1 - pow((1 - 1.0 / M), (K * N))), K);
    }

    /**
     * Calculates the false positive probability with a given number of elements
     * @param elements Number of elements already introduced inside the Bloom Filter
     * @return The probability of getting a false positive depending on the number of elements
     */
    [[nodiscard]] double falsePositive(size_t elements) const {
        return pow((1 - pow((1 - 1.0 / M), (K * elements))), K);
    }

    /**
     * Calculates the best size for the bitmap (M) based on the false positive rate
     * @return best M case depending on the other two values
     */
    [[nodiscard]] double getBestM(double desiredFalseProbability) const {
        return -desiredFalseProbability * log(falsePositive()) / (log(2) * log(2));
    }

    /**
     * Calculates the best number of hash functions (K) for the bloom filter
     * @return best K case depending on the other two values
     */
    [[nodiscard]] double getBestK() const {
        return (log(2) * M / N);
    }

    string toString() const {
        std::ostringstream oss;
        oss << "BloomFilter bitset (" << M << " bits):\n";
        for (size_t i = 0; i < M; ++i) {
            oss << bits.test(i);
        }
        oss << "\n";
        oss << "Posicions amb valor 1:";
        for (size_t i = 0; i < M; ++i) {
            if (bits.test(i)) {
                oss << " [" << i << "]";
            }
        }
        oss << "\nFalse positive rate (theoretical, amb N=" << N << "): " << falsePositive() << "\n";
        return oss.str();
    }
};

#endif //UTILS_BLOOMFILTER_H
