class Solution {
public:
    int BinSearch(long long n) {
        long long s = 0;
        long long e = n;
        long long ans = -1;

        while (s <= e) {
            long long mid = s + (e - s) / 2;
            long long square = (long long)mid * mid; // ✅ cast to long long

            if (square == n) {
                return mid;
            }
            if (square > n) {
                e = mid - 1;
            } else {
                ans = mid;
                s = mid + 1;
            }
        }
        return ans;
    }

    int mySqrt(long long x) {
        return BinSearch(x);
    }
};
