#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        int m = nums.size();
        int half = m / 2;
        long long total = accumulate(nums.begin(), nums.end(), 0LL);

        // Precompute all subset‐sums by bucketed subset‐size
        vector<vector<long long>> sums1(half + 1), sums2(half + 1);
        int lim = 1 << half;
        
        sums1.reserve(lim);
        sums2.reserve(lim);
        for (int mask = 0; mask < lim; ++mask) {
            int cnt = __builtin_popcount(mask);
            long long s1 = 0, s2 = 0;
            for (int i = 0; i < half; ++i) {
                if (mask & (1 << i)) {
                    s1 += nums[i];
                    s2 += nums[half + i];
                }
            }
            sums1[cnt].push_back(s1);
            sums2[cnt].push_back(s2);
        }

        // Sort each bucket
        for (int k = 0; k <= half; ++k) {
            sort(sums1[k].begin(), sums1[k].end());
            sort(sums2[k].begin(), sums2[k].end());
        }

        long long best = LLONG_MAX;
        // For each way to split k from first half, half-k from second half,
        // scan sums1[k] & sums2[half-k] with two pointers.
        for (int k = 0; k <= half; ++k) {
            auto &A = sums1[k];
            auto &B = sums2[half - k];
            int i = 0, j = (int)B.size() - 1;
            // try to make part = A[i] + B[j] ≈ total/2
            while (i < (int)A.size() && j >= 0) {
                long long part = A[i] + B[j];
                long long diff = llabs(total - 2 * part);
                best = min(best, diff);
                // if sum too small, we need larger part => increase A[i] or B[j]
                if (part * 2 < total) {
                    ++i;
                } else {
                    --j;
                }
            }
        }

        return (int)best;
    }
};

// For quick sanity check
// int main() {
//     Solution sol;
//     vector<int> nums = {3,9,7,3};
//     cout << sol.minimumDifference(nums) << "\n";  // 2
// }
