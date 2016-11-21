class Solution {
 public:
  // Instead of 1 -> A, 26 -> Z, we can assume that 0 -> A, 25 -> Z, and then
  // here comes the base 26 representation, it's similar when you convert a
  // number from base 10 to base 2
  string convertToTitle(int n) {
    string result;
    while (n) {
      result.push_back((n - 1) % 26 + 'A');
      n = (n - 1) / 26;
    }
    std::reverse(result.begin(), result.end());
    return result;
  }
};
