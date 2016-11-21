// Copyright (C) 2016 by Yang Liu
class Solution {
public:
  string fractionToDecimal(int numerator, int denominator) {
    if (denominator == 0) return "NAN";
    if (numerator == 0) return "0";
    string res("");
    if (numerator < 0 ^ denominator < 0) res.push_back('-');

    long abs_nume = std::labs(numerator),
                    abs_deno = std::labs(denominator);
    // get interger part
    res += std::to_string(abs_nume / abs_deno);

    abs_nume %= abs_deno;
    if (abs_nume == 0) return res;
    res.push_back('.');

    unordered_map<int, int> visited;
    while (abs_nume) {
      if (visited.find(abs_nume)!=visited.end()) {
        res.insert(res.begin() + visited[abs_nume], '(');
        res.push_back(')');
        break;
      } else {
        visited[abs_nume] = res.size();  // mark the position of res
        abs_nume *= 10;
        res.push_back('0' + abs_nume / abs_deno);
        abs_nume %= abs_deno;
      }
    }
    return res;
  }
};
