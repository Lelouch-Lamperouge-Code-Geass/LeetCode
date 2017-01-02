class Solution {
public:
  bool exist(vector<vector<char>>& board, string word) {
    if(board.empty()) return false;
    for(int i=0;i<board.size();++i){
      for(int j=0;j<board[0].size();++j){
        if(dfs(board,word,i,j,0))
          return true;
      }
    }
    return false;
  }
private:
  bool dfs(vector<vector<char>>& board, const string & word,
           const int row,const int col,const int word_index){
    if(board[row][col] != word[word_index]) return false;
    if(word_index == word.size()-1) return true;

    bool reval(false);
    board[row][col] = '#';
    if(row > 0 && dfs(board,word,row-1,col,word_index+1)
       || row < board.size()-1 && dfs(board,word,row+1,col,word_index+1)
       || col > 0 && dfs(board,word,row,col-1,word_index+1)
       || col < board[0].size()-1 && dfs(board,word,row,col+1,word_index+1)){
      reval = true;
    }
    board[row][col] = word[word_index];//revert back
    return reval;
  }
};
