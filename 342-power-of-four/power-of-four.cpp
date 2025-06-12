class Solution {
public:
    bool isPowerOfFour(int n) {
        if(n<=0) return false;
        if(n==1) return true;
        long long start=1;
        long long end =n-1;
        long long mid=start+(end-start)/2;
        
        while(start<=end){
            if(pow(4,mid)==n) return true;
            if(pow(4,mid)>n){
                end=mid-1;
            }
            if(pow(4,mid)<n){
                start=mid+1;
            }
            mid=start+(end-start)/2;
        }
        return false;
    }
};