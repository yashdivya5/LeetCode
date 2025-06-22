class Solution {
public:
    bool isPerfectSquare(int num) {
        if(num<=0) return false;
        if(num==1) return true;
        long long s=0;
        long long e=num-1;
        long long mid=s+(e-s)/2;
        while(s<=e){
            if(mid*mid==num){
                return true;
            }
            if(mid*mid<num){
                s=mid+1;
            }
            else{
                e=mid-1;
            }
            mid=s+(e-s)/2;
        }
        return false;
    }
};