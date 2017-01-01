
class Solution {
public:
  vector<int> plusOne(vector<int>& digits) {
    const std::size_t digits_size(digits.size());
    std::size_t index(digits_size-1);
    while (index<digits_size) {
      if (digits[index]==9) {
        if (index==0) {
          //only 9999 stuff will be here
          digits[index] = 1;
          digits.push_back(0);
          return digits;
        } else {
          digits[index] = 0;
        }
      } else {
        ++ digits[index];
        return digits;
      }
      -- index;
    }
    return digits;
  }
};
