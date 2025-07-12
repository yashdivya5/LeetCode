class Solution {
public:
    int strongPasswordChecker(string password) {
        int n = password.size();
        bool hasLower = false, hasUpper = false, hasDigit = false;
        for (char c : password) {
            if (islower(c)) hasLower = true;
            else if (isupper(c)) hasUpper = true;
            else if (isdigit(c)) hasDigit = true;
        }
        int missing = (!hasLower) + (!hasUpper) + (!hasDigit);

        vector<int> repeats;
        for (int i = 0; i < n;) {
            int j = i;
            while (i < n && password[i] == password[j]) i++;
            if (i - j >= 3) repeats.push_back(i - j);
        }

        if (n < 6)
            return max(missing, 6 - n);

        int toDelete = max(n - 20, 0);
        int leftDelete = toDelete;
        vector<int> buckets(3, 0);
        for (int len : repeats)
            buckets[len % 3]++;

        int replacements = 0;
        // Step 1: Delete from (len % 3 == 0) groups
        for (int k = 0; k < 3; ++k) {
            for (int i = 0; i < repeats.size() && leftDelete > 0; ++i) {
                if (repeats[i] < 3 || repeats[i] % 3 != k) continue;
                int need = min(leftDelete, repeats[i] - 2 - k); // At most, leave at len==2
                need = max(need, 0); // never negative
                int del = min(leftDelete, k + 1);
                int use = min(del, repeats[i] - 2);
                repeats[i] -= use;
                leftDelete -= use;
            }
        }
        // Step 2: Any remaining deletions applied uniformly to remaining large groups
        for (int i = 0; i < repeats.size() && leftDelete > 0; ++i) {
            if (repeats[i] < 3) continue;
            int del = min(leftDelete, repeats[i] - 2);
            repeats[i] -= del;
            leftDelete -= del;
        }
        // Step 3: Calculate total replacements needed
        for (int len : repeats) {
            if (len >= 3)
                replacements += len / 3;
        }
        return toDelete + max(missing, replacements);
    }
};
