
/*
 * Solution 1, very straightforward
*/

class Solution {
public:
  vector<string> findRepeatedDnaSequences(string s) {
    vector<string> res;
    unordered_map<string,int> visited;
    const int n(s.size());
    for (int i=0;i+10<=n;++i) {
      const string & cur_str = s.substr(i,10);
      if (visited.find(cur_str)!=visited.end() && visited[cur_str]==1) {
        res.push_back(cur_str);
      }
      ++ visited[cur_str];
    }
    return res;
  }
};

/*
 * Solution 2
*/

class Solution {
public:
  //http://www.cnblogs.com/jcliBlogger/p/4600085.html
  //instead of keeping the whole substring, can be convert it to other formats? Well, you have noticed that there are only 4 letters A, T, C, G in the substring. If we assign each letter 2 bits, then a 10-letter substring will only cost 20 bits and can thus be accommodated by a 32-bit integer, greatly lowering the space complexity.
  vector<string> findRepeatedDnaSequences(string s) {
    unordered_map<int,int> counter;
    int hash(0), N(s.size());
    for(int i=0;i<9;++i) hash = ( (hash<<2) & 0xfffff ) | mapping(s[i]) ;
    vector<string> res;
    for(int i=9;i<N;++i){
      hash = ( (hash<<2) & 0xfffff ) | mapping(s[i]) ;
      if(counter[hash]++ ==1){
        res.push_back(s.substr(i-9,10));
      }
    }
    return res;
  }
private:
  // Really doesn't matter here, while I like using gray code here.
  int mapping(char s){
    if (s == 'A') return 0;
    if (s == 'C') return 1;
    if (s == 'G') return 3;
    if (s == 'T') return 2;
    return -1;
  }
};
