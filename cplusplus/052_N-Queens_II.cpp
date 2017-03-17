class Solution {
public:
  int totalNQueens(int n) {
    bool col_marker[n] ={false},
      dia1[2*n-1] ={false}, //45 diagnal
        dia2[2*n-1] ={false};//135 diagnal
        int reval(0);
        backtracking(reval,0,n,col_marker,dia1,dia2);
        return reval;
  }
private:
  void backtracking(int & reval,int row,int n,
                    bool col_marker[],bool dia1[],bool dia2[]){
    if (row==n) {
      ++ reval;
    } else {
      for (int col=0;col<n;++col) {
        int k1 = col-row+n-1, k2 = row+col;
        if (col_marker[col]||dia1[k1]||dia2[k2]){
          continue;
        } else {
          col_marker[col] = dia1[k1] = dia2[k2] = true;
          backtracking(reval,row+1,n,col_marker,dia1,dia2);
          col_marker[col] = dia1[k1] = dia2[k2] = false;
        }
      }
    }
  }
};
