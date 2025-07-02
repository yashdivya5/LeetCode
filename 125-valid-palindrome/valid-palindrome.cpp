class Solution {
public:
    bool isPalindrome(string s) {
        string res;
        for(char ch:s){
            if(isalnum(ch)){
                res+=tolower(ch);
            }
        }
        int st=0;
        int e=res.size()-1;
        while(st<e){
             if(res[st]!=res[e]){
                return false;
            }
            st++;
            e--;
        }
        return true;
    }
};
