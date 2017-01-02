class Solution {
public:
  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    vector<int>  temp;
    Backtracking(res,temp,1,n,k);
    return res;
  }
private:
  void Backtracking(vector<vector<int>> & res, vector<int> & temp, int start,int n,int k){
    if (temp.size()==k) {
      res.push_back(temp);
    } else {
      if (start>n) return;
      // add current item, go to left child
      temp.push_back(start);
      Backtracking(res,temp,start+1,n,k);
      temp.pop_back(); // revert back
      // not add current item,go to right child
      Backtracking(res,temp,start+1,n,k);
    }
  }
};

/*
We can make the recursion tree shorter.
*/
class Solution {
public:
  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    if(k<0 || n<k) return res;
    vector<int> temp;
    backtracking(res,temp,n,k,1);
    return res;
  }
private:
  void backtracking(vector<vector<int>> & res,
                    vector<int>&temp,
                    const int n,
                    const int k,
                    const int start){
    if(temp.size()==k){
      res.push_back(temp);
    } else {
      if(start>n) return;
      for(int i=start;i<=n;++i){
        temp.push_back(i);
        backtracking(res,temp,n,k,i+1);
        temp.pop_back();
      }
    }
  }
};

/*
0 0 #initialization
1 0
1 1 #push_back
1 2 #push_back
1 3 #push_back
1 4 #push_back
1 5
2 5
2 2 #push_back
2 3 #push_back
2 4 #push_back
...
3 4 #push_back
3 5
4 5
4 4
4 5
5 5 #stop
*/
class Solution {
public:
  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> result;
    int i = 0;
    vector<int> p(k, 0);
    while (i >= 0) {
      p[i]++;
      if (p[i] > n) --i;
      else if (i == k - 1) result.push_back(p);
      else {
        ++i;
        p[i] = p[i - 1];
      }
    }
    return result;
  }

};
