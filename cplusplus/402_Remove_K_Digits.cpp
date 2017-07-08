// Solution one
// The first algorithm is straight-forward. Let's think about the simplest case:
// how to remove 1 digit from the number so that the new number is the smallest possible？
// Well, one can simply scan from left to right, and remove the first "peak" digit;
// the peak digit is larger than its right neighbor. One can repeat this procedure k times,
// and obtain the first algorithm.
class Solution {
public:
  string removeKdigits(string num, int k) {
    while (k -- > 0) {
      std::size_t first_peak_pos = FindFirstPeak(num);
      num.erase(first_peak_pos, 1);
    }

    std::size_t first_non_zero = num.find_first_not_of("0");
    if (first_non_zero == std::string::npos) {
      return "0";
    }
    return num.substr(first_non_zero);
  }
private:
  std::size_t FindFirstPeak(const std::string & num) {
    std::size_t pos(0);
    const std::size_t num_size(num.size());
    while (pos < num_size) {
      if (pos + 1 < num_size && num[pos] > num[pos + 1]) {
        return pos;
      }
      ++ pos;
    }

    return num_size - 1;
  }
};

// The above algorithm is a bit inefficient because it frequently remove
// a particular element from a string and has complexity O(k*n).
// One can simulate the above procedure by using a stack, and obtain a O(n) algorithm.
// Note, when the result stack (i.e. res) pop a digit, it is equivalent as remove that "peak" digit.
class Solution {
public:
  string removeKdigits(string num, int k) {
    std::string increasing(""); // Use it as a stack

    num.push_back('0'); // Add a sentinel to handle ["112","1"] case

    for (char c : num) {
      while (!increasing.empty()
             && increasing.back() > c
             && k > 0) {
        increasing.pop_back();
        -- k;
      }

      increasing.push_back(c);
    }

    increasing.pop_back(); // pop back the '0'

    std::size_t first_non_zero = increasing.find_first_not_of("0");
    if (first_non_zero == std::string::npos) {
      return "0";
    }
    return increasing.substr(first_non_zero);
  }
};
