/*
Solution 1:
The space complexity is easy to conclude: the major additional space usage is counter and cur_counter, 
both of which consumes O(words.size()) space.
For the time complexity, it depends on the two for loops. The outer loop will loop for O(s_size) times 
and the inner loop will loop for O(word_amount) times. So the time complexity is at most O(s_size * word_amount).
*/
class Solution {
public:
  vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> reval;
    if (s.empty() || words.empty()) return reval;
    // We know that the words have same length
    const int word_len(words[0].size()), word_amount(words.size()),
      words_total_len(word_len*word_amount);
    // It doesn't say words have duplicate or not
    // So have to use hahsmap here
    std::unordered_map<std::string,int> counter;
    for (const std::string & word : words) {
      ++ counter[word];
    }
    const int s_size(s.size());
    for (int i=0;i+words_total_len<=s_size;++i) {
      int remain_count(word_amount); // how many words left to be found
      std::unordered_map<std::string,int> cur_counter(counter);
      for (int j=i;remain_count>0 && j+word_len<=s_size;j+=word_len){
        const std::string & cur_word = s.substr(j,word_len);
        if (-- cur_counter[cur_word] ==  -1)
          break;
        -- remain_count;
      }
      if (remain_count==0) reval.push_back(i);
    }
    return reval;
  }
};

/*
Solution 2: 119ms
*/
class Solution {
public:
  vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> res;
    if(s.empty() || words.empty()) return res;
    const int s_size(s.size()),word_len(words[0].size()),word_num(words.size()),
      word_len_combi(word_len * word_num);
    if(s_size < word_len_combi) return res;
    unordered_map<string, int> mapper;
    for(const string & word : words){
      mapper.find(word) == mapper.end() ? mapper[word] = 1 : ++mapper[word];
    }

    int start(0),cur(0),word_num_remain(word_num);
    for(int i=0;i<word_len;++i){
      start = cur = i;
      while(start <= s_size-word_len*word_num_remain){
        const string cur_word(s.substr(cur,word_len));
        if(mapper.find(cur_word) == mapper.end()){
          //Not found, reset
          for(word_num_remain = word_num; start!=cur; start+=word_len) {
            ++mapper[s.substr(start,word_len)];
          }
          start += word_len; //skip the current invalid word;
        } else if(mapper[cur_word]==0){
          //Already found, reset
          for(; cur_word!=s.substr(start,word_len);start+=word_len){
            ++ mapper[s.substr(start,word_len)];
            ++ word_num_remain;
          }
          start += word_len; //skip the previous found one;
        } else {
          -- mapper[cur_word];
          if(--word_num_remain == 0){
            res.push_back(start);
            ++ mapper[s.substr(start,word_len)];
            start += word_len;
            ++ word_num_remain;
          }
        }
        cur += word_len;
      }

      for(;start<cur;start+=word_len)  ++mapper[s.substr(start,word_len)];//reset the map count
    }
    return res;
  }
};

/* Solution 3 : 22ms */
class Solution {
public:
  vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> res;
    if(s.empty() || words.empty()) return res;
    const int s_size(s.size()),word_len(words[0].size()),word_num(words.size()),
      word_len_combi(word_len * word_num);
    if(s_size < word_len_combi) return res;
    unordered_map<string, int> mapper;
    for(const string & word : words){
      mapper.find(word) == mapper.end() ? mapper[word] = 1 : ++mapper[word];
    }

    int start(0),cur(0),word_num_remain(word_num);
    for(int i=0;i<word_len;++i){
      start = cur = i;
      while(start <= s_size-word_len*word_num_remain){
        const string cur_word(s.substr(cur,word_len));
        if(mapper.find(cur_word) == mapper.end()){
          //Not found, reset
          for(word_num_remain = word_num; start!=cur; start+=word_len) {
            ++mapper[s.substr(start,word_len)];
          }
          start += word_len; //skip the current invalid word;
        } else if(mapper[cur_word]==0){
          //Already found, reset
          for(; cur_word!=s.substr(start,word_len);start+=word_len){
            ++ mapper[s.substr(start,word_len)];
            ++ word_num_remain;
          }
          start += word_len; //skip the previous found one;
        } else {
          -- mapper[cur_word];
          if(--word_num_remain == 0){
            res.push_back(start);
            ++ mapper[s.substr(start,word_len)];
            start += word_len;
            ++ word_num_remain;
          }
        }
        cur += word_len;
      }

      for(;start<cur;start+=word_len)  ++mapper[s.substr(start,word_len)];//reset the map count
    }
    return res;
  }
};
