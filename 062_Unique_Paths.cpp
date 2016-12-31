class Solution {
public:
  int uniquePaths(int m, int n) {
    vector<int> pathCount(n,1);
    for (int i=1;i<m;++i) {
      for (int j=1;j<n;++j){
        pathCount[j] += pathCount[j-1];
      }
    }
    return pathCount[n-1];
  }
};
