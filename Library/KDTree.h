#ifndef UTILS_KDTREE_H
#define UTILS_KDTREE_H

#include <bits/stdc++.h>
using namespace std;

template <typename T, size_t K>
class KDTree {
public:
    /**
     * Default constructor
     */
    KDTree() : root(nullptr) {}

    /**
     * Constructor from an array
     */
    KDTree(array<T, K> arr[], size_t length) {
        vector<array<T, K>> points(arr, arr + length);
        root = build(points, 0);
    }

private:
    // Node structure for the KDTree
    struct KDNode {
        // Point in K dimensions
        array<T, K> point;
        // Childs of current node
        KDNode *left, *right;

        // Constructor to initialize a Node
        explicit KDNode(const array<T, K> pt) : point(pt), left(nullptr), right(nullptr) {}
    };

    // Root of the KDTree
    KDNode *root;

    // Recursive function to insert a point into the KDTree
    KDNode *insert(KDNode *node, const array<T, K>point, size_t depth) {
        // If there's no node to go to, we create a new one
        if (node == nullptr) return new KDNode(point);

        // Calculate current dimension (cd)
        size_t cd = depth % K;

        // Compare point with current node and decide to go left or right
        if (point[cd] < node->point[cd])
            node->left = insert(node->left, point, depth + 1);
        else
            node->right = insert(node->right, point, depth + 1);

        return node;
    }

    // Recursive function to search for a point in the KDTree
    bool search(KDNode *node, const array<T, K>point, size_t depth) const {
        // Base case: If node is null, the point is not found
        if (node == nullptr) return false;

        // If the current node matches the point, return true
        if (node->point == point) return true;

        // Calculate current dimension (cd)
        size_t cd = depth % K;

        // Compare point with current node and decide to go left or right
        if (point[cd] < node->point[cd])
            return search(node->left, point, depth + 1);
        else
            return search(node->right, point, depth + 1);
    }

    KDNode* build(vector<array<T, K>>& points, size_t depth) {
        if (points.empty()) return nullptr;

        size_t cd = depth % K;
        size_t median_index = points.size() / 2;

        // Ordenem els punts segons la dimensió actual
        nth_element(points.begin(), points.begin() + median_index, points.end(),
                    [cd](const array<T, K>& a, const array<T, K>& b) {
                        return a[cd] < b[cd];
                    });

        // Creem el node amb la mediana
        auto* node = new KDNode(points[median_index]);

        // Construïm recursivament els subarbres
        vector<array<T, K>> left_points(points.begin(), points.begin() + median_index);
        vector<array<T, K>> right_points(points.begin() + median_index + 1, points.end());

        node->left = build(left_points, depth + 1);
        node->right = build(right_points, depth + 1);

        return node;
    }

    pair<array<T, K>, T> nearest(KDNode* node, const array<T, K>& target, size_t depth, array<T, K> best, T best_dist) const {
        if (node == nullptr) return {best, best_dist};

        T dist = distance_squared(node->point, target);
        if (dist < best_dist) {
            best = node->point;
            best_dist = dist;
        }

        size_t cd = depth % K;
        KDNode *next = nullptr, *other = nullptr;
        if (target[cd] < node->point[cd]) {
            next = node->left;
            other = node->right;
        } else {
            next = node->right;
            other = node->left;
        }

        tie(best, best_dist) = nearest(next, target, depth + 1, best, best_dist);

        T diff = target[cd] - node->point[cd];
        if (diff * diff < best_dist) {
            tie(best, best_dist) = nearest(other, target, depth + 1, best, best_dist);
        }

        return {best, best_dist};
    }

    T distance_squared(const array<T, K>& a, const array<T, K>& b) const {
        T dist = 0;
        for (size_t i = 0; i < K; i++) {
            T d = a[i] - b[i];
            dist += d * d;
        }
        return dist;
    }

    KDNode* remove(KDNode* node, const array<T, K>& point, size_t depth) {
        if (node == nullptr) return nullptr;

        size_t cd = depth % K;

        if (node->point == point) {
            // Cas amb fill dret
            if (node->right) {
                KDNode* minNode = findMin(node->right, cd, depth + 1);
                node->point = minNode->point;
                node->right = remove(node->right, minNode->point, depth + 1);
            }
                // Cas amb només fill esquerre
            else if (node->left) {
                KDNode* minNode = findMin(node->left, cd, depth + 1);
                node->point = minNode->point;
                node->right = remove(node->left, minNode->point, depth + 1);
                node->left = nullptr;
            }
                // Fulla
            else {
                delete node;
                return nullptr;
            }
            return node;
        }

        if (point[cd] < node->point[cd])
            node->left = remove(node->left, point, depth + 1);
        else
            node->right = remove(node->right, point, depth + 1);

        return node;
    }

    KDNode* findMin(KDNode* node, size_t d, size_t depth) {
        if (node == nullptr) return nullptr;

        size_t cd = depth % K;

        if (cd == d) {
            if (node->left == nullptr) return node;
            return findMin(node->left, d, depth + 1);
        }

        KDNode* leftMin = findMin(node->left, d, depth + 1);
        KDNode* rightMin = findMin(node->right, d, depth + 1);
        KDNode* minNode = node;

        if (leftMin && leftMin->point[d] < minNode->point[d]) minNode = leftMin;
        if (rightMin && rightMin->point[d] < minNode->point[d]) minNode = rightMin;

        return minNode;
    }

    void toStringHelper(KDNode* node, size_t depth, ostringstream& oss) const {
        if (!node) return;
        // Indentació segons el nivell
        for (size_t i = 0; i < depth; ++i) oss << "\t";
        oss << "(";
        for (size_t i = 0; i < K; ++i) {
            oss << node->point[i];
            if (i + 1 < K) oss << ", ";
        }
        oss << ")\n";

        toStringHelper(node->left, depth + 1, oss);
        toStringHelper(node->right, depth + 1, oss);
    }

public:

    // Public function to insert a point into the KDTree
    void insert(const array<T, K>point) {
        root = insert(root, point, 0);
    }

    // Public function to search for a point in the KDTree
    bool search(const array<T, K>point) const {
        return search(root, point, 0);
    }

    // Public function to remove a point int the KDTree
    void remove(const array<T, K>& point) {
        root = remove(root, point, 0);
    }

    // Public function to get the nearest neighbor of a point in the KDTree
    array<T, K> nearest_neighbor(const array<T, K>& target) const {
        if (!root) throw runtime_error("Arbre buit");
        return nearest(root, target, 0, root->point, distance_squared(root->point, target)).first;
    }

    string toString() const {
        ostringstream oss;
        toStringHelper(root, 0, oss);
        return oss.str();
    }
};

#endif //UTILS_KDTREE_H
