#ifndef UTILS_SKIPLIST_H
#define UTILS_SKIPLIST_H

#include <bits/stdc++.h>
using namespace std;

// Class for Skip list
template <typename T>
class SkipList {
    /**
     * Node structure
     */
    class SkipListNode {
    public:
        T key;
        // Different level pointers
        SkipListNode **forward;

        SkipListNode(T value, int level) {
            key = value;

            // Generate and initialize foward array
            forward = new SkipListNode *[level + 1];
            memset(forward, 0, sizeof(SkipListNode *) * (level + 1));
        }
    };

    // Maximum level for this skip list
    int MAXLVL;

    // P is the fraction of the nodes per level
    float P;

    // current level of skip list
    int level;

    // pointer to header node
    SkipListNode *header;
public:
    SkipList(int LEVEL_LIMIT, float FRACTION) {
        MAXLVL = LEVEL_LIMIT;
        P = FRACTION;
        level = 0;

        // create header node and initialize key to the default type value
        header = new SkipListNode(T{}, MAXLVL);
    }

    // create random level for node
    int randomLevel() {
        float r = (float) rand() / RAND_MAX;
        int lvl = 0;
        while (r < P && lvl < MAXLVL) {
            lvl++;
            r = (float) rand() / RAND_MAX;
        }
        return lvl;
    }

    // create new node
    SkipListNode *createNode(T key, int level) {
        SkipListNode *n = new SkipListNode(key, level);
        return n;
    }

    // Insert given key in skip list
    void insertElement(T key) {
        SkipListNode *current = header;

        // create update array and initialize it
        SkipListNode *update[MAXLVL + 1];
        memset(update, 0, sizeof(SkipListNode *) * (MAXLVL + 1));

        /* start from highest level of skip list
            move the current pointer forward while key
            is greater than key of node next to current
            Otherwise inserted current in update and
            move one level down and continue search
        */
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != NULL &&
                   current->forward[i]->key < key)
                current = current->forward[i];
            update[i] = current;
        }

        /* reached level 0 and forward pointer to
        right, which is desired position to
        insert key.
        */
        current = current->forward[0];

        /* if current is NULL that means we have reached
        to end of the level or current's key is not equal
        to key to insert that means we have to insert
        node between update[0] and current node */
        if (current == NULL || current->key != key) {
            // Generate a random level for node
            int rlevel = randomLevel();

            // If random level is greater than list's current
            // level (node with highest level inserted in
            // list so far), initialize update value with pointer
            // to header for further use
            if (rlevel > level) {
                for (int i = level + 1; i <= rlevel; ++i)
                    update[i] = header;

                // Update the list current level
                level = rlevel;
            }

            // create new node with random level generated
            SkipListNode *n = createNode(key, rlevel);

            // insert node by rearranging pointers
            for (int i = 0; i <= rlevel; ++i) {
                n->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = n;
            }
        }
    }

    // Check if a key exists in the skip list
    bool contains(T key) const {
        SkipListNode *current = header;

        // Start from the highest level of the skip list
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != NULL && current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }

        // Move to the next node on level 0
        current = current->forward[0];

        // Check if current node has the key we're searching for
        return (current != NULL && current->key == key);
    }

    // Delete a key from the skip list
    void deleteElement(T key) {
        SkipListNode *current = header;

        // Array to store pointers that need to be updated
        SkipListNode *update[MAXLVL + 1];
        memset(update, 0, sizeof(SkipListNode *) * (MAXLVL + 1));

        // Start from the top level and move down to level 0
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        // Move to the next node on level 0
        current = current->forward[0];

        // If current node is the one to delete
        if (current != nullptr && current->key == key) {
            // Update all levels where current node appears
            for (int i = 0; i <= level; i++) {
                if (update[i]->forward[i] != current)
                    break;
                update[i]->forward[i] = current->forward[i];
            }

            // Free memory
            delete[] current->forward;
            delete current;

            // Adjust the level of the skip list
            while (level > 0 && header->forward[level] == nullptr) {
                level--;
            }
        }
    }

    // Display skip list level wise
    string toString() {
        string s = "*****Skip List*****\n";
        for (int i = 0; i <= level; ++i) {
            SkipListNode *node = header->forward[i];
            s += "Level " + to_string(i) + ": ";
            if(node != NULL) {
                s += to_string(node->key);
                node = node->forward[i];
                while (node != NULL) {
                    s += ", " + to_string(node->key);
                    node = node->forward[i];
                }
            }
            s += "\n";
        }
        return s;
    }

    vector<vector<T>> getData() {
        vector<vector<T>> matrix;
        for (int i = 0; i <= level; ++i) {
            SkipListNode *node = header->forward[i];
            matrix.push_back(vector<T>());
            while (node != NULL) {
                matrix[i].push_back(node->key);
                node = node->forward[i];
            }
        }
        return matrix;
    }
};



#endif //UTILS_SKIPLIST_H
