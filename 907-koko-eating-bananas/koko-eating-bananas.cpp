class Solution {
public:
    bool isPos(vector<int>& arr, int h, int k) {
       long long hours=0;
       for(int i=0; i<arr.size();i++){
        hours += (int)ceil((double)arr[i] / k);
       }
       if(hours<=h){
        return true;
       }
       else{
        return false;
       }
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        int s = 1;
        int e = *max_element(piles.begin(), piles.end());;
        int ans = e;
        int mid = s + (e - s) / 2;
        while (s <= e) {
            if (isPos(piles, h, mid)) {
                ans = mid;
                e = mid - 1;
            } else {
                s = mid + 1;
            }
            mid = s + (e - s) / 2;
        }
        return ans;
    }
};