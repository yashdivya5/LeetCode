class Solution {
public:
    int reverse(int x) {
        int num=0;
        while(x!=0){
            int rem=x%10;
            if (num > INT_MAX / 10 || (num == INT_MAX / 10 && rem > 7)) return 0;
            if (num < INT_MIN / 10 || (num == INT_MIN / 10 && rem < -8)) return 0;
            num=num*10+rem;
            x=x/10;
        }
        return num;
    }
};