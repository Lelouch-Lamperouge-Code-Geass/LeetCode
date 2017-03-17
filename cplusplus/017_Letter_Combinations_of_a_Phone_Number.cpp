class Solution {
public:
  vector<string> letterCombinations(string digits) {
    if (digits.empty()) return vector<string>();
    vector<string> res(1,"");
    for (char c : digits) {
      vector<string> temp;
      string letters = DigitToLetter(c);
      for (const string & pre : res) {
        for (char letter : letters) {
          temp.push_back(pre);
          temp.back().push_back(letter);
        }
      }
      res = temp;
    }
    return res;
  }
private:
  string DigitToLetter(char c){
    switch (c) {
    case '2' : return "abc";
    case '3' : return "def";
    case '4' : return "ghi";
    case '5' : return "jkl";
    case '6' : return "mno";
    case '7' : return "pqrs";
    case '8' : return "tuv";
    case '9' : return "wxyz";
    default : return "";
    }
  }
};
