class Solution {
public:
int getSumOfSquares(int n) {
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }
    return sum;
}
    bool isHappy(int n) {
        int num = n;
        for(int i=0; i<1000; ++i){
            num=getSumOfSquares(num);
        }
        if(num==1){
            return true;
        }
        return false;
    }
    
};