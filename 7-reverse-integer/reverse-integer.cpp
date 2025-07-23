class Solution {
public:
    int reverse(int x) {
        if (x >= 0) {
            string str = to_string(x);
            std::reverse(str.begin(), str.end());
            long long a = stoll(str);  // Use stoll for 64-bit conversion
            if (a > INT_MAX) return 0;
            return (int)a;
        } else {
            string str = to_string(x);
            str.erase(0, 1);
            std::reverse(str.begin(), str.end());
            long long a = stoll(str);  // Use stoll for 64-bit conversion
            if (-a < INT_MIN) return 0;
            return (int)(-a);
        }
    }
};
