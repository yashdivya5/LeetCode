#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int strongPasswordChecker(string s) {
        int n = s.size();

        /* 1. Character categories */
        bool hasLower = false, hasUpper = false, hasDigit = false;
        for (char c : s) {
            if (islower(c)) hasLower = true;
            else if (isupper(c)) hasUpper = true;
            else if (isdigit(c)) hasDigit = true;
        }
        int missing = (!hasLower) + (!hasUpper) + (!hasDigit);

        /* 2. Collect only repeating runs that matter (len ≥ 3) */
        vector<int> runs;          // run lengths ≥ 3
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && s[j] == s[i]) ++j;
            int len = j - i;
            if (len >= 3) runs.push_back(len);
            i = j;
        }

        /* 3a. Too short */
        if (n < 6)
            return max(missing, 6 - n);

        /* 3b. Within limits */
        if (n <= 20) {
            int repl = 0;
            for (int len : runs) repl += len / 3;
            return max(missing, repl);
        }

        /* 3c. Too long — need deletions */
        int over = n - 20;

        /* Bucket runs by len % 3 */
        vector<int> b0, b1, b2;
        for (int len : runs) {
            if (len % 3 == 0)      b0.push_back(len);
            else if (len % 3 == 1) b1.push_back(len);
            else                   b2.push_back(len);
        }

        /* Delete 1 from runs ≡ 0 (mod 3) */
        for (int &len : b0) {
            if (!over) break;
            int del = min(1, over);
            len -= del;   over -= del;
        }

        /* Delete 2 from runs ≡ 1 (mod 3) */
        for (int &len : b1) {
            if (!over) break;
            int del = min(2, over);
            len -= del;   over -= del;
        }

        /* Delete the rest from any run in blocks of 3 */
        vector<int> all;
        all.insert(all.end(), b0.begin(), b0.end());
        all.insert(all.end(), b1.begin(), b1.end());
        all.insert(all.end(), b2.begin(), b2.end());

        for (int &len : all) {
            if (!over) break;
            if (len < 3) continue;
            int del = min(over, len - 2);  // keep at least 2 chars
            len -= del;   over -= del;
        }

        /* Recompute replacements after deletions */
        int repl = 0;
        for (int len : all) repl += len / 3;

        return (n - 20) + max(missing, repl);
    }
};
