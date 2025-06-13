class Solution {
public:
    bool isPowerOfThree(int n) {
        long long start=0;
        long long end=20;
        long long mid=start+(end-start)/2;
        if(n<=0) return false;
        // if(n==1) return true;
        while(start<=end){
            if((pow(3,mid))==n) return true;
            if((pow(3,mid))>n){
                end=mid-1;
            }
            if((pow(3,mid)<n)){
                start=mid+1;
            }
            mid=start+(end-start)/2;
        }
        return false;
    }
};