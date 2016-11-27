class TrieNode {
public:
  TrieNode():m_end_here(0),m_children(26,nullptr) {}
<<<<<<< HEAD
  ~TrieNode() { for (TrieNode* child,m_children) delete child;}
=======
  ~TrieNode() { for (TrieNode* child : m_children) delete child;}
>>>>>>> refs/remotes/origin/master
  int m_end_here;
  vector<TrieNode*> m_children;
};

class Trie {
public:
<<<<<<< HEAD
  Trie():m_root(new TireNode()){}
  ~Trie(){delete m_root}
=======
  Trie():m_root(new TrieNode()){}
  ~Trie() { delete m_root; }
>>>>>>> refs/remotes/origin/master
  void AddWord(const string & word) {
    TrieNode* curr(m_root);
    for (char c : word) {
      int i = c - 'a';
<<<<<<< HEAD
      if (!m_children[i]) m_children[i] = new TrieNode();
      curr = m_children[i];
=======
      if (!curr->m_children[i]) curr->m_children[i] = new TrieNode();
      curr = curr->m_children[i];
>>>>>>> refs/remotes/origin/master
    }
    ++ curr->m_end_here;
  }
  TrieNode* m_root;
};

class Solution {
public:
  vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
<<<<<<< HEAD
=======
    if (board.empty()) return vector<string>();
>>>>>>> refs/remotes/origin/master
    Trie trie;
    for (const string & word : words) {
      trie.AddWord(word);
    }
<<<<<<< HEAD
    vector<string> reval;
=======
    unordered_set<string> reval;
>>>>>>> refs/remotes/origin/master
    string temp;
    const int m(board.size()),n(board[0].size());
    for (int i=0;i<m;++i) {
      for (int j=0;j<n;++j) {
        find(board,i,j,trie.m_root,reval,temp);
      }
    }
<<<<<<< HEAD
    return reval;
  }
private:
  void find(vector< vector<char> > & board,
            int i,
            int j,
            TrieNode* node,
            vector<string> & reval,
            stirng & temp) {
    const int row_size(board.size()), col_size(board[0].size());
    if (i<0 || i>=row_size || j<0 || j>=col_size) return;
    if (!node) return;
    if (node->m_end_here > 0) {
      reval.push_back(temp);
    }
    node = node->m_children[board[i][j] - 'a'];
    temp.push_back(board[i][j]);
    find(board,i+1,j,node,reval,temp);
    find(board,i-1,j,node,reval,temp);
    find(board,i,j+1,node,reval,temp);
    find(board,i,j-1,node,reval,temp);
    temp.pop_back(); // revert back
  }
};


















=======
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
>>>>>>> refs/remotes/origin/master
