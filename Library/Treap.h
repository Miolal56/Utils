#ifndef UTILS_TREAP_H
#define UTILS_TREAP_H

// C++ program to demonstrate search, insert and delete in Treap
#include <bits/stdc++.h>
using namespace std;

template<typename T, typename Compare = less<T>>
class Treap {
private:
    /**
     * Node structure
     */
    class TreapNode {
    public:
        T key;
        int priority;
        TreapNode *left, *right;

        TreapNode(T value, int probability) : key(value), priority(probability), left(nullptr), right(nullptr) {}

        TreapNode* rightRotate(TreapNode* y) {
            TreapNode* x = y->left;
            TreapNode* T2 = x->right;

            // Perform rotation
            x->right = y;
            y->left = T2;

            // Return new root
            return x;
        }

        TreapNode* leftRotate(TreapNode* x) {
            TreapNode* y = x->right;
            TreapNode* T2 = y->left;

            // Perform rotation
            y->left = x;
            x->right = T2;

            // Return new root
            return y;
        }

        void inorder() {
            left->inorder();
            cout << "key: " << key << " | priority: " << priority;
            if (left != nullptr)
                cout << " | left child: " << left->key;
            if (right != nullptr)
                cout << " | right child: " << right->key;
            cout << endl;
            right->inorder();
        }

        vector<T> getVector() {
            vector<T> output, tmp;
            if (left != nullptr)
                output = left->getVector();
            output.push_back(key);
            if (right != nullptr)
                tmp = right->getVector();
            output.insert(output.end(), tmp.begin(), tmp.end());
            return output;
        }
    };

public:
    /**
     * Default constructor
     */
    Treap() : root(nullptr) {}

    /**
     * Comparador de l'estructura
     */
    Compare cmp;

    /**
     * Constructor of a Tream from a given TreamNode
     * @param tr Given TreamNode which will became the root
     */
    explicit Treap(TreapNode *tr) : root(tr) {}

    bool isEmpty(){
        return root == nullptr;
    }

private:

    /**
     * Main node of the structure
     */
    TreapNode *root;

    /**
     * Method that creates a new node
     * @param key Creates a new node for the given value
     * @return TreapNode pointer with the given value
     */
    TreapNode *newNode(T key) {
        return new TreapNode(key, rand() % 100);
    }

    /**
     * Recursive method used to search a given key in the given TreapNode object
     * @param root TreapNode where the value will be searched
     * @param key Value to be searched
     * @return TreapNode pointer to the node with the requested value
     */
    TreapNode *searchAux(TreapNode *root, T key) {
        // Base Cases: root is null or key is present at root
        if (root == nullptr || root->key == key) return root;

        // Key is greater than root's key
        if (cmp(root->key, key)) return searchAux(root->right, key);

        // Key is smaller than root's key
        return searchAux(root->left, key);
    }

    /**
     * Recursive method used to insert a given value in the given TreapNode Object
     * @param root TreapNode where the value will me inserted
     * @param key Value to be inserted
     * @return TreapNode pointer to the node with the new node
     */
    TreapNode* insertAux(TreapNode* root, T key) {
        if (!root)
            return newNode(key);

        if (root->priority < rand() % 100) {
            TreapNode* new_node = newNode(key);
            split(root, key, new_node->left, new_node->right);
            return new_node;
        }

        if (!cmp(root->key, key))
            root->left = insertAux(root->left, key);
        else
            root->right = insertAux(root->right, key);

        return root;
    }

    /**
     * Recursive method used to delete a given value in the given TreapNode Object
     * @param root TreapNode where the value will me deleted
     * @param key Value to be deleted
     * @return TreapNode pointer to the node with the deleted node
     */
    TreapNode* deleteNodeAux(TreapNode* root, T key) {
        if (!root) return nullptr;

        if (root->key == key) {
            TreapNode* merged = merge(root->left, root->right);
            delete root;
            return merged;
        }

        if (cmp(key, root->key))
            root->left = deleteNodeAux(root->left, key);
        else
            root->right = deleteNodeAux(root->right, key);

        return root;
    }

    /**
     * Split treap into left and right by key
     * @param current Current node to be separated
     * @param key Current value on the node
     * @param left Left child of the node
     * @param right Right child of the node
     */
    void split(TreapNode* current, const T& key, TreapNode*& left, TreapNode*& right) {
        if (!current) {
            left = right = nullptr;
            return;
        }
        if (!cmp(key, current->key)) {  // current->key <= key ?
            // current belongs to left subtree
            split(current->right, key, current->right, right);
            left = current;
        } else {
            // current->key > key
            split(current->left, key, left, current->left);
            right = current;
        }
    }

    // Merge two treaps left and right assuming all keys in left <= keys in right
    TreapNode* merge(TreapNode* left, TreapNode* right) {
        if (!left || !right)
            return left ? left : right;

        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            return left;
        } else {
            right->left = merge(left, right->left);
            return right;
        }
    }

    void inorderAux(TreapNode* node) const {
        if (!node) return;
        inorderAux(node->left);
        cout << "key: " << node->key << " | priority: " << node->priority;
        if (node->left) cout << " | left child: " << node->left->key;
        if (node->right) cout << " | right child: " << node->right->key;
        cout << endl;
        inorderAux(node->right);
    }

public:
    /**
     * Public method used to search a given key
     * @param key Element to be searched in the Treap
     * @return TreapNode Pointer of the given value
     */
    TreapNode *search(T key) {
        return searchAux(root, key);
    }

    /**
     * Public method used to insert a given value
     * @param key Element to be inserted into the Treap
     * @return TreapNode Pointer of the node with the new value
     */
    TreapNode* insert(T key) {
        root = insertAux(root, key);
        return root;
    }

    /**
     * Public method used to delete a given value in the given TreapNode Object
     * @param key Element to be deleted from the Treap
     * @return TreapNode Pointer of the node with the deleted value
     */
    TreapNode* deleteNode(T key) {
        root = deleteNodeAux(root, key);
        return root;
    }

    void inorder() const {
        inorderAux(root);
    }

    vector<T> getVector() {
        vector<T> output, tmp;
        if (root) {
            if (root->left)
                output = root->left->getVector();
            output.push_back(root->key);
            if (root->right)
                tmp = root->right->getVector();
            output.insert(output.end(), tmp.begin(), tmp.end());
        }
        return output;
    }
};

#endif //UTILS_TREAP_H
