#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        const int m = nums.size();          // 2 × n  (0 < m ≤ 30)
        const int n = m / 2;               // size of each half
        const long long TOTAL = accumulate(nums.begin(), nums.end(), 0LL);

        /* ------------------------------------------------------------
           1. Enumerate ALL subset-sums of each half, bucketed by size.
           ------------------------------------------------------------ */
        vector<vector<long long>> leftSums(n + 1), rightSums(n + 1);

        const int LIM = 1 << n;            // 2ⁿ  (≤ 32 768)
        for (int mask = 0; mask < LIM; ++mask) {
            int bits = __builtin_popcount(mask);

            long long lSum = 0, rSum = 0;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    lSum += nums[i];           // element in left half
                    rSum += nums[i + n];       // element in right half
                }
            }
            leftSums[bits].push_back(lSum);    // choose ‘bits’ from left half
            rightSums[bits].push_back(rSum);   // choose same ‘bits’ from right half
        }

        /* ------------------------------------------------------------
           2. Sort every bucket so we can two-pointer scan later.
           ------------------------------------------------------------ */
        for (int k = 0; k <= n; ++k) {
            sort(leftSums[k].begin(),  leftSums[k].end());
            sort(rightSums[k].begin(), rightSums[k].end());
        }

        /* ------------------------------------------------------------
           3. For each possible split (k from left, n−k from right),
              sweep the two sorted lists with a two-pointer technique
              to find the closest pair whose total is TOTAL/2.
           ------------------------------------------------------------ */
        long long best = LLONG_MAX;

        for (int k = 0; k <= n; ++k) {
            const auto& A = leftSums[k];          // size k  (ascending)
            const auto& B = rightSums[n - k];     // size n−k (ascending)
            if (A.empty() || B.empty()) continue;

            int i = 0, j = (int)B.size() - 1;
            while (i < (int)A.size() && j >= 0) {
                long long part = A[i] + B[j];     // sum of one candidate n-element subset
                best = min(best, llabs(TOTAL - 2 * part));

                // If part * 2 is still less than TOTAL, we need a larger sum.
                // Otherwise we need a smaller one.
                if (part * 2 < TOTAL) ++i;
                else                   --j;
            }
        }

        return static_cast<int>(best);  // |diff| ≤ 30×10⁷ < 2³¹, safe cast
    }
};
