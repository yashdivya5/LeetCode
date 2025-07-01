class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> v;
        int i=0,j=0,k=0;
        while(i<m && j<n){
            if(nums1[i]<=nums2[j]){
               v.push_back(nums1[i]);
                k++;
                i++;
            }
            else{
                v.push_back(nums2[j]);
                k++;
                j++;
            }
        }
        while(i<m){
            v.push_back(nums1[i]);
            k++;
            i++;
        }
        while(j<n){
            v.push_back(nums2[j]);
            k++;
            j++;
        }
        for(int a=0;a<nums1.size();a++){
            nums1[a]=v[a];
        }
    }
};