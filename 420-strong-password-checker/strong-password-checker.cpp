class Solution {
public:
    int strongPasswordChecker(string password) {
        int n = password.length();

        bool hasLower = false, hasUpper = false, hasDigit = false;
        for (char c : password) {
            if (islower(c)) hasLower = true;
            else if (isupper(c)) hasUpper = true;
            else if (isdigit(c)) hasDigit = true;
        }

        int missingTypes = (!hasLower) + (!hasUpper) + (!hasDigit);

        // Count sequences with 3 or more repeating characters
        vector<int> repeats;
        for (int i = 2; i < n;) {
            if (password[i] == password[i - 1] && password[i - 1] == password[i - 2]) {
                int len = 2;
                while (i < n && password[i] == password[i - 1]) {
                    len++;
                    i++;
                }
                repeats.push_back(len);
            } else {
                i++;
            }
        }

        if (n < 6) {
            return max(missingTypes, 6 - n);
        } else if (n <= 20) {
            int replace = 0;
            for (int len : repeats) {
                replace += len / 3;
            }
            return max(missingTypes, replace);
        } else {
            int toDelete = n - 20;
            int replace = 0;

            // Optimize deletions
            vector<int> temp = repeats;
            for (int i = 0; i < temp.size(); ++i) {
                int len = temp[i];
                if (toDelete <= 0) break;

                if (len % 3 == 0) {
                    int del = min(toDelete, 1);
                    temp[i] -= del;
                    toDelete -= del;
                }
            }
            for (int i = 0; i < temp.size(); ++i) {
                int len = temp[i];
                if (toDelete <= 0) break;

                if (len % 3 == 1) {
                    int del = min(toDelete, 2);
                    temp[i] -= del;
                    toDelete -= del;
                }
            }
            for (int i = 0; i < temp.size(); ++i) {
                int len = temp[i];
                if (toDelete <= 0) break;

                int del = min(toDelete, len - 2);
                temp[i] -= del;
                toDelete -= del;
            }

            for (int len : temp) {
                if (len >= 3) {
                    replace += len / 3;
                }
            }

            return (n - 20) + max(missingTypes, replace);
        }
    }
};
