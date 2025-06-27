#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>
#include <functional>
#include <string>
using namespace std;

template <typename T, typename Compare = less<T>>
class SplayTree {
    /**
     * Node structure
     */
    class SplayTreeNode {
    public:
        // Data of the node
        T key;
        // Node on the left and on the right
        SplayTreeNode *left, *right;

        SplayTreeNode() : key(), left(nullptr), right(nullptr) {}

        explicit SplayTreeNode(T newData) : key(newData), left(nullptr), right(nullptr) {}

        SplayTreeNode(const SplayTreeNode &node) {
            key = node.key;
            left = node.left ? new SplayTreeNode(*node.left) : nullptr;
            right = node.right ? new SplayTreeNode(*node.right) : nullptr;
        }

        ~SplayTreeNode() {
            delete left;
            delete right;
        }
    };

public:
    SplayTree() : root(nullptr) {}

    explicit SplayTree(T data) : root(new SplayTreeNode(data)) {}

private:
    SplayTreeNode* root;

    Compare cmp;

    SplayTreeNode* searchAux(SplayTreeNode *node, T key) {
        if (node == nullptr || (!cmp(key, node->key) && !cmp(node->key, key))) return node;

        if (cmp(key, node->key)) {
            if (node->left == nullptr) return node;

            if (cmp(key, node->left->key)) {
                node->left->left = searchAux(node->left->left, key);
                node = rightRotate(node);
            } else if (cmp(node->left->key, key)) {
                node->left->right = searchAux(node->left->right, key);
                if (node->left->right != nullptr)
                    node->left = leftRotate(node->left);
            }
            return (node->left == nullptr) ? node : rightRotate(node);
        } else {
            if (node->right == nullptr) return node;

            if (cmp(key, node->right->key)) {
                node->right->left = searchAux(node->right->left, key);
                if (node->right->left != nullptr)
                    node->right = rightRotate(node->right);
            } else if (cmp(node->right->key, key)) {
                node->right->right = searchAux(node->right->right, key);
                node = leftRotate(node);
            }
            return (node->right == nullptr) ? node : leftRotate(node);
        }
    }

    SplayTreeNode* insertData(SplayTreeNode* node, T key) {
        if (node == nullptr) return new SplayTreeNode(key);

        node = searchAux(node, key);

        if ((!cmp(key, node->key) && !cmp(node->key, key))) return node;

        auto newNode = new SplayTreeNode(key);
        if (cmp(key, node->key)) {
            newNode->right = node;
            newNode->left = node->left;
            node->left = nullptr;
        } else {
            newNode->left = node;
            newNode->right = node->right;
            node->right = nullptr;
        }
        return newNode;
    }

    SplayTreeNode* rightRotate(SplayTreeNode* x) {
        SplayTreeNode* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    SplayTreeNode* leftRotate(SplayTreeNode* x) {
        SplayTreeNode* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    string toStringAux(SplayTreeNode* node, const string& tab) {
        string s;
        if (node != nullptr) {
            s = tab + to_string(node->key) + "\n";
            s += tab + "left:\n";
            s += toStringAux(node->left, tab + "\t");
            s += tab + "right:\n";
            s += toStringAux(node->right, tab + "\t");
        }
        return s;
    }

    SplayTreeNode* deleteAux(SplayTreeNode* node, T key) {
        if (!node) return nullptr;

        // Primer fem splay del node a eliminar
        node = searchAux(node, key);

        // Si la clau no és la que volem, retornem el node com està
        if (node->key != key) return node;

        SplayTreeNode* temp;

        // Cas 1: només subarbre dret o cap
        if (!node->left) {
            temp = node;
            node = node->right;
        }
            // Cas 2: només subarbre esquerre
        else {
            temp = node;

            // Fem splay del màxim del subarbre esquerre (per portar-lo al root)
            node = searchAux(node->left, key);
            // Connectem el subarbre dret al nou root
            node->right = temp->right;
        }

        // Alliberem el node eliminat
        temp->left = temp->right = nullptr;
        delete temp;

        return node;
    }

public:
    void insert(T key) {
        root = insertData(root, key);
    }

    void deleteKey(T key) {
        root = deleteAux(root, key);
    }

    bool search(T key) {
        root = searchAux(root, key);
        return (root && (!cmp(key, root->key) && !cmp(root->key, key)));
    }

    string toString() {
        return toStringAux(root, "");
    }
};

#endif