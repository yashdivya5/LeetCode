class Solution {
public:

    int BinSearch(int n){
        long long s=0;
        long long e=n;
        long long mid=s+(e-s)/2;
        long long ans=-1;

        while(s<=e){
            long long square = mid*mid;
            if(square == n){
                return mid;
            }
            if(square>n){
                e=mid-1;
            }
            else{
                ans=mid;
                s=mid+1;
            }
            mid=s+(e-s)/2;
        }
        return ans;
    }
    int mySqrt(long long x) {
        return BinSearch(x);
    }
};