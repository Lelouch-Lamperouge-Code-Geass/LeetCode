class Solution {
public:
  bool wordPattern(string pattern, string str) {
    istringstream iss(str);
    string word;
    unordered_map<char, int> char_mapper;
    unordered_map<string,int> str_mapper;
    int index(0);
    while(iss >> word){
      if(char_mapper[pattern[index]] != str_mapper[word]){ // Please notice that here the default value is 0,thats why
        // we can't use 0 as the value.
        return false;
      }
      char_mapper[pattern[index]] = str_mapper[word] = index;//record index + 1 to avoid default 0, in that words, use length as the value
      ++ index;
    }
    return index == pattern.size();
  }
};
