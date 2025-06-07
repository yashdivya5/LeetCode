class Solution {
public:

    bool isPos(vector<int>&arr,int m, int k,int mid){
        int numBouq=0;
        int count=0;
        for(int i=0;i<arr.size();i++){
            if(arr[i]<=mid){
                count++;
                if(count==k){
                numBouq++;
                count=0;
            }
            }
            else{
                count=0;
            }
            
        }
        if(numBouq<m){
            return false;
        }
        else{
            return true;
        }
        
    }
    int minDays(vector<int>& bloomDay, int m, int k) {
        int s=*min_element(bloomDay.begin(), bloomDay.end());;
        int e=*max_element(bloomDay.begin(),bloomDay.end());
        int mid=s+(e-s)/2;
        int ans=-1;
        while(s<=e){
            if(isPos(bloomDay,m,k,mid)){
                ans=mid;
                e=mid-1;
            }
            else{
                s=mid+1;
            }
            mid=s+(e-s)/2;
        }
        return ans;
    }
};