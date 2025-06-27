/**
 * @Title: Longest Common Prefix
 * @Link: https://leetcode.com/problems/longest-common-prefix/description/?envType=problem-list-v2&envId=trie
 */

#include "../Trie.h"

class Solution {
public:
    char voc[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    string longestCommonPrefix(vector<string>& strs) {
        Trie trie(voc, 26);
        for(string s : strs) trie.put(s);
        return solve(trie.getRootNode());
    }

    string solve(Trie::TrieNode* node){
        if(node->isWord) return "";
        string sol = "";
        int index;
        bool last = false;
        for(int i = 0; i < 26; ++i){
            if(node->childs[i] != nullptr) {
                last = node->childs[i]->isWord;
                sol += voc[i], index = i;
            }
        }
        if(sol.size() != 1) return "";
        if(last) return sol;
        return sol + solve(node->childs[index]);
    }
};