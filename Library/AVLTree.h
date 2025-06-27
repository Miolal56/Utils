#ifndef UTILS_AVLTREE_H
#define UTILS_AVLTREE_H

#include <iostream>
using namespace std;

template <typename T, typename Compare = less<T>>
class AVLTree {
    /**
     * Node structure
     */
    class AVLTreeNode {
    public:
        T data;
        size_t heigth;
        AVLTreeNode *left, *right;

        AVLTreeNode() : data(), left(nullptr), right(nullptr), heigth(1) {}

        explicit AVLTreeNode(T newData) : data(newData), left(nullptr), right(nullptr), heigth(1) {}

        AVLTreeNode(const AVLTreeNode &node) {
            data = node.data;
            left = node.left ? new AVLTreeNode(*node.left) : nullptr;
            right = node.right ? new AVLTreeNode(*node.right) : nullptr;
            heigth = node.heigth;
        }

        ~AVLTreeNode() {
            delete left;
            delete right;
        }
    };

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        delete root;
    }

private:
    // Root node of the structure
    AVLTreeNode* root;

    // Method to compare between elements
    Compare cmp;

    void insertData(const T &newData, AVLTreeNode *&node) {
        if (node == nullptr) {
            node = new AVLTreeNode(newData);
        } else {
            if (cmp(newData, node->data)) {
                insertData(newData, node->left);
            } else if (cmp(node->data, newData)) {
                insertData(newData, node->right);
            }
        }

        updateHeight(node);
        node = balance(node); // Balance the node after insertion
    }

    bool searchData(const T &data, AVLTreeNode *node) const {
        if (node == nullptr) return false;
        if (cmp(data, node->data)) {
            return searchData(data, node->left);
        } else if (cmp(node->data, data)) {
            return searchData(data, node->right);
        }
        return true; // Found the node
    }

    size_t height(AVLTreeNode* node) const {
        return node ? node->heigth : 0;
    }

    void updateHeight(AVLTreeNode* node) {
        if (node) {
            node->heigth = 1 + max(height(node->left), height(node->right));
        }
    }

    int getBalance(AVLTreeNode* node) {
        return node ? static_cast<int>(height(node->left)) - static_cast<int>(height(node->right)) : 0;
    }

    AVLTreeNode* balance(AVLTreeNode* node) {
        if (node == nullptr) return node;

        int balanceFactor = getBalance(node);

        if (balanceFactor > 1) {
            if (getBalance(node->left) >= 0) {
                return rightRotate(node);
            } else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        } else if (balanceFactor < -1) {
            if (getBalance(node->right) <= 0) {
                return leftRotate(node);
            } else {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;
    }

    AVLTreeNode* rightRotate(AVLTreeNode* y) {
        AVLTreeNode* x = y->left;
        AVLTreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLTreeNode* leftRotate(AVLTreeNode* x) {
        AVLTreeNode* y = x->right;
        AVLTreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLTreeNode* findMin(AVLTreeNode* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    void removeData(const T &data, AVLTreeNode* &node) {
        if (!node) return;

        if (cmp(data, node->data)) {
            removeData(data, node->left);
        } else if (cmp(node->data, data)) {
            removeData(data, node->right);
        } else {
            // Node with only one child or no child
            if (!node->left || !node->right) {
                AVLTreeNode* temp = node->left ? node->left : node->right;
                delete node;
                node = temp;
            } else {
                // Node with two children: Get the inorder successor (smallest in the right subtree)
                AVLTreeNode* temp = findMin(node->right);
                node->data = temp->data;
                removeData(temp->data, node->right);
            }
        }

        if (node == nullptr) return;

        updateHeight(node);
        node = balance(node); // Rebalance the tree
    }

    string toStringAux(AVLTreeNode* node) const {
        if (!node) return "";

        string leftStr = toStringAux(node->left);
        string rightStr = toStringAux(node->right);

        if(node->left && node->right) return "(" + to_string(node->data) + " " + leftStr + ", " + rightStr + ")";
        else if(node->right) return "(" + to_string(node->data) + " _, " + rightStr + ")";
        return "(" + to_string(node->data) + " " + leftStr + ", _)";
    }

public:
    void insert(const T &newData) {
        insertData(newData, root);
    }

    bool search(const T &data) const {
        return searchData(data, root);
    }

    void remove(const T &data) {
        removeData(data, root);
    }

    string toString(){
        if(root == nullptr) return "()";
        return toStringAux(root);
    }
};

#endif //UTILS_AVLTREE_H