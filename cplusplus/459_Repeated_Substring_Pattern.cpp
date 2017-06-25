// Solution one
class Solution {
public:
  bool repeatedSubstringPattern(string s) {
    if (s.empty()) return true;
    const std::size_t s_size(s.size());

    for (std::size_t len = s_size / 2; len >= 1; --len) {
      if (s_size % len == 0) {
        std::size_t repeated_times(s_size / len);
        bool match_pattern(true);
        const std::string & substring = s.substr(0, len);
        for (std::size_t i = 0; i < repeated_times; ++i) {
          if (s.substr(i * len, len) != substring) {
            match_pattern = false;
            break;
          }
        }
        if (match_pattern) return true;
      }
    }

    return false;
  }
};

// Solution two
// Consider a string S="helloworld".
// Now, given another string T="lloworldhe", can we figure out if T is a rotated version of S?
// Yes, we can! We check if S is a substring of T+T.
// How do we apply that to this problem? We consider every rotation of string S such
// that it's rotated by k units [k < len(S)] to the left.
// Specifically, we're looking at strings "elloworldh", "lloworldhe", "loworldhel", etc...
// If we have a string that is periodic (i.e. is made up of strings that are the same and repeat R times),
// then we can check if the string is equal to some rotation of itself, and if it is, then we know that the string is periodic.
// Checking if S is a sub-string of (S+S)[1:-1] basically checks if the string is present
// in a rotation of itself for all values of R such that 0 < R < len(S).

class Solution {
public:
  bool repeatedSubstringPattern(string s) {
    const std::string & ss = s + s;
    const std::string & p = ss.substr(1, ss.size() - 2); // No first and last char

    return p.find(s) != std::string::npos;
  }
};

