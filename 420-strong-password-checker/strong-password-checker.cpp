#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <queue>

using namespace std;

class Solution {
public:
    /**
     * @brief Calculates the minimum number of steps to make a password strong.
     * * A strong password has:
     * 1. Length between 6 and 20.
     * 2. At least one lowercase letter, one uppercase letter, and one digit.
     * 3. No three consecutive repeating characters.
     * * The solution is broken down into three cases based on the password length.
     * * @param password The input password string.
     * @return The minimum number of operations (insert, delete, replace) required.
     */
    int strongPasswordChecker(string password) {
        int n = password.length();

        // Step 1: Calculate the number of missing character types.
        bool has_lower = false, has_upper = false, has_digit = false;
        for (char c : password) {
            if (islower(c)) has_lower = true;
            if (isupper(c)) has_upper = true;
            if (isdigit(c)) has_digit = true;
        }
        int missing_types = (!has_lower) + (!has_upper) + (!has_digit);

        // Case 1: Password length is less than 6.
        if (n < 6) {
            // We must insert at least `6 - n` characters.
            // These insertions can also fulfill missing type requirements.
            // The total number of operations is the maximum of the length deficit
            // and the number of missing types.
            return max(6 - n, missing_types);
        }

        // For n >= 6, we first identify all repeating sequences of 3 or more.
        vector<int> repeats;
        if (n > 0) {
            int count = 1;
            for (int i = 1; i < n; ++i) {
                if (password[i] == password[i - 1]) {
                    count++;
                } else {
                    if (count >= 3) {
                        repeats.push_back(count);
                    }
                    count = 1;
                }
            }
            if (count >= 3) {
                repeats.push_back(count);
            }
        }

        // Case 2: Password length is between 6 and 20.
        if (n <= 20) {
            int replacements_needed = 0;
            for (int L : repeats) {
                // For a sequence of length L, we need L/3 replacements.
                replacements_needed += L / 3;
            }
            // Each replacement can fix a repeating sequence AND a missing type.
            // So, the total number of operations is the maximum of these two needs.
            return max(missing_types, replacements_needed);
        }

        // Case 3: Password length is greater than 20.
        // We must delete `n - 20` characters. These are mandatory operations.
        int deletes_needed = n - 20;
        int total_ops = deletes_needed;

        // The deletions can also help fix repeating sequences. We want to use them
        // greedily to reduce the number of replacements needed later.
        // To save 1 replacement, we need to apply `k` deletions to a group.
        // - A group of length L where L%3==0 (e.g., 6) needs 1 deletion. Cost=1.
        // - A group of length L where L%3==1 (e.g., 7) needs 2 deletions. Cost=2.
        // - A group of length L where L%3==2 (e.g., 8) needs 3 deletions. Cost=3.
        
        int replacements_needed = 0;
        // A priority queue stores the cost (1, 2, or 3 deletions) to save one replacement.
        priority_queue<int, vector<int>, greater<int>> costs;
        for (int L : repeats) {
            replacements_needed += L / 3;
            if (L >= 3) {
                costs.push((L % 3) + 1);
            }
        }
        
        // Greedily apply deletions to the "cheapest" groups first to save one replacement per group.
        while (deletes_needed > 0 && !costs.empty()) {
            int cost = costs.top();
            costs.pop();
            if (deletes_needed >= cost) {
                deletes_needed -= cost;
                replacements_needed--;
            }
        }
        
        // *** FIX ***
        // After the initial cheap saves, we might have leftover deletions.
        // Any 3 further deletions can reduce the number of replacements by 1.
        if (deletes_needed > 0) {
            replacements_needed -= deletes_needed / 3;
        }
        
        // After deletions, the number of remaining operations is the max of
        // missing types and the (now reduced) number of replacements for repeats.
        // The number of replacements cannot be negative.
        total_ops += max(missing_types, max(0, replacements_needed));
        
        return total_ops;
    }
};