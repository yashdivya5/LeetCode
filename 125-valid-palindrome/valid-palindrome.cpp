class Solution {
public:
    bool isPalindrome(string s) {
        string cleaned = "";
        for (char c : s) {
            if (isalnum(c))
                cleaned += tolower(c);
        }
        int n = cleaned.length();
        for (int i = 0; i < n / 2; ++i) {
            if (cleaned[i] != cleaned[n - i - 1])
                return false;
        }

        return true;
    }
};
