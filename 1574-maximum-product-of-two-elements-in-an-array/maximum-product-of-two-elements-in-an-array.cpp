class Solution {
public:
    int maxProduct(vector<int>& nums) {
        vector<int> v;
        int res=0;
        for(int i=0;i<nums.size();i++){
            for(int j=i+1;j<nums.size();j++){
                res=(nums[i]-1)*(nums[j]-1);
                v.push_back(res);
            }
        }
        int maxi=*max_element(v.begin(),v.end());
        return maxi;
    }
};