#ifndef RADIXTREE_H
#define RADIXTREE_H

#include <bits/stdc++.h>
using namespace std;

class RadixTree {
    /**
     * Node structure
     */
public:
    class RadixTreeNode {
    public:
        string value;
        bool isTerminal;
        unordered_map<char, RadixTreeNode *> childs;

        RadixTreeNode() : value(), childs(), isTerminal(false) {}

        explicit RadixTreeNode(string data, bool isWord) : value(data), childs(), isTerminal(isWord) {}

        ~RadixTreeNode() {
            value = "";
            childs.clear();
        }
    };

public:
    RadixTree() : root() {}

    RadixTreeNode* getRootNode() {
        return root;
    }

private:
    RadixTreeNode *root;

    void insert(RadixTreeNode *node, const string &data, const int &index) {
        int found = 0;
        for (const auto child: node->childs) {
            //printf("?%c (equal to %c) %s\n", child.first, data[index], child.second->value.c_str());
            if (data[index] != child.first) continue;
            found = 1;
            int count = compare(child.second->value, data, index);
            //printf(" -> %d\n", count);
            switch (count) {
                case -1:
                    //printf("new index: %d\n", child.second->value.size());
                    insert(child.second, data, child.second->value.size());
                    break;
                case -2:
                    break;
                default:
                    RadixTreeNode *newParent = new RadixTreeNode(data.substr(0, count), false);
                    //printf("&%s\n", newParent->value.c_str());
                    newParent->childs.emplace(child.second->value[count], child.second);
                    newParent->childs.emplace(data[count], new RadixTreeNode(data, true));
                    node->childs.erase(child.first);
                    node->childs.emplace(newParent->value[index], newParent);
            }
            break;
        }
        if (!found) {
            node->childs.emplace(data[index], new RadixTreeNode(data, true));
        }
    }

    int compare(const string &value, const string &data, const int &index) {
        auto mismatch_pair = mismatch(value.begin() + index, value.end(), data.begin() + index);
        int count = mismatch_pair.first - (value.begin() + index);
        //printf("%d", count);
        if (index + count == value.size() && index + count == data.size()) return -2;
        if (index + count == value.size()) return -1;
        return count;
    }

    string toString(RadixTreeNode *node, string tab) {
        stringstream ss;
        ss << tab << node->value << "\n";
        if (node->childs.size()) ss << tab << "Childs:\n";
        else ss << tab << "- No childs -\n";
        for (const auto child: node->childs) {
            ss << tab << "\t(" << child.first << ")" << "\n";
            ss << toString(child.second, tab + "\t");
        }
        return ss.str();
    }

    bool search(RadixTreeNode *node, const string &data, const int &index) {
        if (index > data.size()) return false;
        for (auto child: node->childs) {
            //printf("? %c\n", child.first);
            if (child.first != data[index]) continue;
            if(compare(child.second->value, data, index) >= 0) return false;
            //printf("%c %s in %s (%s)\n", child.first, child.second->value.c_str(), data.substr(index, data.size()).c_str(), data.c_str());
            return search(child.second, data, child.second->value.size());
        }
        if (index == data.size()) return node->isTerminal;
        return false;
    }

public:
    bool isEmpty() { return root == nullptr; }
    void clear() { delete root; root = nullptr; }

    bool search(const string &element) {
        return search(root, element, 0);
    }

    void insert(const string &element) {
        if (root == nullptr) root = new RadixTreeNode();
        insert(root, element, 0);
    }

    string toString() {
        stringstream ss;
        if (root->childs.size()) ss << "Childs:\n";
        else ss << "- No childs -\n";
        for (const auto child: root->childs) {
            ss << toString(child.second,  "\t") << '\n';
        }
        return ss.str();
    }
};

#endif //RADIXTREE_H
