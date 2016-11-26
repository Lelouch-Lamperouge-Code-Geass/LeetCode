class TrieNode {
public:
  TrieNode():m_end_here(0),m_children(26,nullptr) {}
  ~TrieNode() { for (TrieNode* child : m_children) delete child;}
  int m_end_here;
  vector<TrieNode*> m_children;
};

class Trie {
public:
  Trie():m_root(new TrieNode()){}
  ~Trie() { delete m_root; }
  void AddWord(const string & word) {
    TrieNode* curr(m_root);
    for (char c : word) {
      int i = c - 'a';
      if (!curr->m_children[i]) curr->m_children[i] = new TrieNode();
      curr = curr->m_children[i];
    }
    ++ curr->m_end_here;
  }
  TrieNode* m_root;
};

class Solution {
public:
  vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    if (board.empty()) return vector<string>();
    Trie trie;
    for (const string & word : words) {
      trie.AddWord(word);
    }
    unordered_set<string> reval;
    string temp;
    const int m(board.size()),n(board[0].size());
    for (int i=0;i<m;++i) {
      for (int j=0;j<n;++j) {
        find(board,i,j,trie.m_root,reval,temp);
      }
    }
    return vector<string>(reval.begin(),reval.end());
  }
private:
   void find(vector< vector<char> > & board,
            int i,
            int j,
            TrieNode* node,
            unordered_set<string> & reval,
            string & temp) {
        const int row_size(board.size()), col_size(board[0].size());
    	if (i<0 || i>=row_size || j<0 || j>=col_size || board[i][j]=='#' || !node) return;
        if( node->m_children[board[i][j] - 'a'] ) {
    		temp.push_back(board[i][j]);
    		node = node->m_children[board[i][j] - 'a'];
    		if (node->m_end_here > 0) reval.insert(temp);
    		
    		const char original_char = board[i][j];
    		board[i][j] ='#';
    		find(board,i+1,j,node,reval,temp);
    		find(board,i-1,j,node,reval,temp);
    		find(board,i,j+1,node,reval,temp);
    		find(board,i,j-1,node,reval,temp);
    		temp.pop_back(); // revert back
    		board[i][j] = original_char;
    	}
    }
};
