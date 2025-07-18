class Solution {
public:
    int strongPasswordChecker(string password) {
        int n = password.length();
        int missing = getMissingTypes(password);
        
        if (n < 6) {
            return max(6 - n, missing);
        }
        
        vector<int> repeats;
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && password[j] == password[i]) 
                j++;
            int len = j - i;
            if (len >= 3) 
                repeats.push_back(len);
            i = j;
        }
        
        if (n <= 20) {
            int replace = 0;
            for (int len : repeats) 
                replace += len / 3;
            return max(missing, replace);
        }
        
        int to_del = n - 20;
        vector<int> mod0, mod1, mod2;
        int replace_total = 0;
        for (int len : repeats) {
            replace_total += len / 3;
            if (len % 3 == 0) 
                mod0.push_back(len);
            else if (len % 3 == 1) 
                mod1.push_back(len);
            else 
                mod2.push_back(len);
        }
        
        int save = 0;
        for (int i = 0; i < mod0.size() && to_del > 0; i++) {
            to_del--;
            save++;
        }
        
        for (int i = 0; i < mod1.size() && to_del >= 2; i++) {
            to_del -= 2;
            save++;
        }
        
        for (int i = 0; i < mod2.size() && to_del >= 3; i++) {
            to_del -= 3;
            save++;
        }
        
        replace_total -= save;
        replace_total -= to_del / 3;
        replace_total = max(0, replace_total);
        
        return (n - 20) + max(missing, replace_total);
    }
    
private:
    int getMissingTypes(const string& password) {
        bool hasLower = false, hasUpper = false, hasDigit = false;
        for (char c : password) {
            if (islower(c)) hasLower = true;
            else if (isupper(c)) hasUpper = true;
            else if (isdigit(c)) hasDigit = true;
        }
        int missing = 0;
        if (!hasLower) missing++;
        if (!hasUpper) missing++;
        if (!hasDigit) missing++;
        return missing;
    }
};
