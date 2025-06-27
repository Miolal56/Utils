#include "../SegmentTree.h"

class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        auto maxOp = [](int a, int b) { return max(a, b); };
        SegmentTree<int> segTree(baskets, maxOp, INT_MIN);

        int unplaced = 0;

        for (int fruit : fruits) {
            int left = 0, right = baskets.size() - 1, bestIndex = -1;

            // Binary search to find the first basket that can hold the fruit
            while (left <= right) {
                int mid = left + (right - left) / 2;
                int maxCapacity = segTree.get(left, mid); // Query max in this range

                if (maxCapacity >= fruit) {
                    bestIndex = mid;
                    right = mid - 1; // Try finding a better (earlier) basket
                } else {
                    left = mid + 1;
                }
            }

            if (bestIndex == -1) {
                unplaced++; // No basket could hold this fruit
            } else {
                segTree.remove(bestIndex); // Remove basket
            }
        }

        return unplaced;
    }
};