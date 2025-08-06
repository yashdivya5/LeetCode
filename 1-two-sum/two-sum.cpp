class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int>seen;

        for(int i=0;i<nums.size();i++){
            int comp=target-nums[i];
            if(seen.count(comp)) return {seen[comp],i};
            seen[nums[i]]=i;
        }
        return {};
        
    }
};