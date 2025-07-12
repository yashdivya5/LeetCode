#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        int m = nums.size();
        int half = m / 2;
        long long total = 0;
        for (auto &x : nums) total += x;
        
        // sums1[k]: all possible sums from first half choosing k elements
        // sums2[k]: all possible sums from second half choosing k elements
        vector<vector<long long>> sums1(half + 1), sums2(half + 1);
        
        // Process first half
        for (int mask = 0; mask < (1 << half); ++mask) {
            int cnt = __builtin_popcount(mask);
            long long s = 0;
            for (int i = 0; i < half; ++i) {
                if (mask & (1 << i)) {
                    s += nums[i];
                }
            }
            sums1[cnt].push_back(s);
        }
        
        // Process second half
        for (int mask = 0; mask < (1 << half); ++mask) {
            int cnt = __builtin_popcount(mask);
            long long s = 0;
            for (int i = 0; i < half; ++i) {
                if (mask & (1 << i)) {
                    s += nums[half + i];
                }
            }
            sums2[cnt].push_back(s);
        }
        
        // Sort each sums2 bucket for binary search
        for (int k = 0; k <= half; ++k) {
            sort(sums2[k].begin(), sums2[k].end());
        }
        
        long long best = LLONG_MAX;
        // We need to choose exactly half elements in total:
        // choose k from first half and (half - k) from second half.
        for (int k = 0; k <= half; ++k) {
            for (long long s1 : sums1[k]) {
                auto &vec = sums2[half - k];
                // target sum for s2 to get close to total/2
                double tgt = (double)total / 2 - s1;
                auto it = lower_bound(vec.begin(), vec.end(), tgt);
                
                // check candidate at it
                if (it != vec.end()) {
                    long long s2 = *it;
                    long long part = s1 + s2;
                    long long diff = llabs(total - 2 * part);
                    best = min(best, diff);
                }
                // check previous candidate
                if (it != vec.begin()) {
                    --it;
                    long long s2 = *it;
                    long long part = s1 + s2;
                    long long diff = llabs(total - 2 * part);
                    best = min(best, diff);
                }
            }
        }
        
        return (int)best;
    }
};

// Example usage:
// int main() {
//     Solution sol;
//     vector<int> nums = {3, 9, 7, 3};
//     cout << sol.minimumDifference(nums) << "\n";  // Output: 2
//     return 0;
// }
