class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;
        long long d1=(long long)dividend;
        long long d2=(long long)divisor;
        return d1/d2;
    }
};