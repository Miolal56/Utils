#ifndef UTILS_SEGMENTTREE_H
#define UTILS_SEGMENTTREE_H

#include <iostream>
#include <vector>

using namespace std;

template<typename T = int>
class SegmentTree {
    class SegmentNode {
    public:
        T from, to, mid, value;
        SegmentNode *left, *right;

        SegmentNode(T f, T t, const vector<T>& arr, T (*op)(T, T)) {
            from = f;
            to = t;
            mid = (from + to) / 2;
            if (f == t) {
                left = right = nullptr;
                value = arr[f];
            } else {
                left = new SegmentNode(f, mid, arr, op);
                right = new SegmentNode(mid + 1, t, arr, op);
                value = op(left->value, right->value);
            }
        }

        ~SegmentNode() {
            delete left;
            delete right;
        }
    };

    SegmentNode *root;
    T (*operation)(T, T); // Store the function pointer
    T neutral;

public:
    SegmentTree(const vector<T>& arr, T (*op)(T, T), T value) {
        if (arr.empty()) {
            root = nullptr;
        } else {
            root = new SegmentNode(0, arr.size() - 1, arr, op);
        }
        operation = op;
        neutral = value;
    }

    ~SegmentTree() {
        delete root;
    }

    T get(T from, T to) {
        return get(from, to, root);
    }

    void update(int index, T value) {
        return update(index, value, root);
    }

    void remove(int index) {
        remove(index, root);
    }

    string toString() const {
        ostringstream oss;
        toStringHelper(root, oss, 0);
        return oss.str();
    }

private:
    T get(T from, T to, SegmentNode *node) {
        if (!node) return neutral;
        if (node->from == from && node->to == to) return node->value;

        if (to <= node->mid)
            return get(from, to, node->left);
        else if (from > node->mid)
            return get(from, to, node->right);
        else
            return operation(get(from, node->mid, node->left), get(node->mid + 1, to, node->right));
    }

    void remove(int index, SegmentNode* node) {
        if (!node) return;

        if (node->from == node->to) { // Leaf node
            node->value = neutral; // Effectively remove this basket
            return;
        }

        if (index <= node->mid)
            remove(index, node->left);
        else
            remove(index, node->right);

        node->value = operation(node->left->value, node->right->value); // Update tree
    }

    void update(int index, T value, SegmentNode* node) {
        if (!node) return;

        if (node->from == node->to) { // Leaf node
            node->value = value; // Effectively update this basket
            return;
        }

        if (index <= node->mid)
            update(index, value, node->left);
        else
            update(index, value, node->right);

        node->value = operation(node->left->value, node->right->value); // Update tree
    }

    void toStringHelper(SegmentNode* node, ostringstream& oss, int depth) const {
        if (!node) return;
        // Tabulacions segons profunditat
        for (int i = 0; i < depth; ++i) {
            oss << '\t';
        }
        // Imprimir rang i valor del node
        oss << "[" << node->from << ", " << node->to << "]: " << node->value << "\n";

        toStringHelper(node->left, oss, depth + 1);
        toStringHelper(node->right, oss, depth + 1);
    }
};

#endif //UTILS_SEGMENTTREE_H
