#ifndef UTILS_TRIE_H
#define UTILS_TRIE_H

#include <bits/stdc++.h>
using namespace std;

class Trie {
    /**
     * Node structure
     */
public:
    class TrieNode {
    public:
        bool isWord;
        int length;
        TrieNode** childs;

        /**
         * Default constructor
        */
        TrieNode() : isWord(false), childs(nullptr) {}

        /**
         * Main constructor
         * @param dimension Number of letters
         */
        TrieNode(int dimension) {
            this->isWord = false;
            this->childs = new TrieNode*[dimension]();
            this->length = dimension;
        }

        /**
         * Method to delete a node
         */
        ~TrieNode() {
            for (int i = 0; i < length; ++i) {
                delete childs[i];
            }
            delete[] childs;
        }
    };

public:
    /**
     * Default constructor
     */
    Trie() : root(nullptr), length(0) {}

    /**
     * Constructor from vocabulary
     */
    Trie(const char* vocabulary, const int len) {
        length = len;
        while (vocabulary[length] != '\0') ++length;
        root = new TrieNode(length);
        for (int i = 0; i < length; ++i) {
            selector[vocabulary[i]] = i;
        }
    }

    ~Trie() {
        delete root;
    }

    TrieNode* getRootNode() {
        return root;
    }

private:
    /**
     * Main Node of the structure
     */
    TrieNode* root;
    /**
     * Contains the index of each letter
     */
    unordered_map<char, int> selector;
    /**
     * Contains the length of the vocabulary
     */
    int length;

    /**
     * Public methods for the usage of the class
     */

public:
    /**
     * Method to add elements to the structure
     * @param s Element to add
     */
    void put(const string &s) {
        TrieNode* current = root;
        for (char ch : s) {
            if (current->childs[selector[ch]] == nullptr) {
                current->childs[selector[ch]] = new TrieNode(length);
            }
            current = current->childs[selector[ch]];
        }
        current->isWord = true;
    }

    /**
     * Method to search if an element is inside the structure
     * @param s Element to search for
     * @return Returns true if the element is contained, if not, returns false
     */
    bool search(const string &s) {
        TrieNode* current = root;
        for (char ch : s) {
            if (current->childs[selector[ch]] == nullptr) return false;
            current = current->childs[selector[ch]];
        }
        return current->isWord;
    }

    /**
     * Method to remove an element from the structure
     * @param s Element to remove
     */
    void remove(const string &s) {
        TrieNode* current = root;
        for (char ch : s) {
            if (current->childs[selector[ch]] == nullptr) return;
            current = current->childs[selector[ch]];
        }
        current->isWord = false;
    }

    string toString() const {
        ostringstream oss;
        toStringHelper(root, oss, 0, "");
        return oss.str();
    }

private:
    void toStringHelper(TrieNode* node, ostringstream& oss, int depth, string prefix) const {
        if (node == nullptr) return;

        // Afegeix tabulacions segons la profunditat
        for (int i = 0; i < depth; ++i) {
            oss << '\t';
        }

        // Mostra el prefix actual i si és final de paraula
        oss << (prefix.empty() ? "*" : prefix);
        if (node->isWord) oss << " (word)";
        oss << '\n';

        // Recorre tots els fills
        for (const auto& kv : selector) {
            char ch = kv.first;
            int index = kv.second;
            TrieNode* child = node->childs[index];
            if (child != nullptr) {
                toStringHelper(child, oss, depth + 1, prefix + ch);
            }
        }
    }
};

#endif //UTILS_TRIE_H
