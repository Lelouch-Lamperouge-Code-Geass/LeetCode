/*
  Straight forward way to solve the problem in 3 steps:
  1. find the length of the number where the nth digit is from
  2. find the actual number where the nth digit is from
  3. find the nth digit and return
*/

class Solution {
public:
  int findNthDigit(int n) {
    std::size_t num_pos(1), nine(9), digits_len(1);

    while (n > digits_len * nine) {
      n -= digits_len * nine;
      digits_len += 1; // digits_len is 1,2,3,4,.....
      nine *= 10; // 9, 90, 900,... nine represents how many numbers have 1,2,3,... digits
      num_pos *= 10; // 10, 100, 1000
    }

    num_pos += (n - 1) / digits_len;
    std::string num_str = std::to_string(num_pos);
    return num_str[(n - 1) % digits_len] - '0';

  }
};
