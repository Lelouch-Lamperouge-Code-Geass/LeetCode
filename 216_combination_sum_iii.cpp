class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        vector<int> temp;
        dfs(res,temp,k,n,1);
        return res;
    }
private:
    void dfs(vector<vector<int>> & res, 
            vector<int> & temp,
            const int k,
            const int n,
            const int start) {
        if (temp.size()==k && n==0) {
            res.push_back(temp);
        } else {
            if (temp.size()==k || n==0) return;
            for (int i=start;i<=9;++i) {
                if (i>n) break;
                temp.push_back(i);
                dfs(res,temp,k,n-i,i+1);
                temp.pop_back();
            }
        }
    }
};
