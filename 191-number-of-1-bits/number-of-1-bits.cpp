class Solution {
public:
    int hammingWeight(int n) {
        int count=0;
        int i=0;
        int bin[32];
        while(n>0){
            bin[i]=n%2;
            n=n/2;
            i++;
            
        }
        for(int j=0; j<i;j++){
            if(bin[j]==1){
                count++;
            }
        }
        return count;
        
    }
};