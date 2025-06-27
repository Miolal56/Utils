/**
 * @Title: Longest Common Prefix
 * @Link: https://leetcode.com/problems/longest-common-prefix/description/?envType=problem-list-v2&envId=trie
 */

#include "../RadixTree.h"

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        RadixTree radixTree;
        for(string s : strs) radixTree.insert(s);
        if(radixTree.getRootNode()->childs.size() != 1) return "";
        return radixTree.getRootNode()->childs.at(strs[0][0])->value;
    }
};