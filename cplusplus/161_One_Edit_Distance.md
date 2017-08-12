Given two strings S and T, determine if they are both one edit distance apart.

# Solution

__Note that if two strings are the same, should return false because their edit distance is zero.__

```
/*
 * There're 3 possibilities to satisfy one edit distance apart: 
 * 
 * 1) Replace 1 char:
 	  s: a B c
 	  t: a D c
 * 2) Delete 1 char from s: 
	  s: a D  b c
	  t: a    b c
 * 3) Delete 1 char from t
	  s: a   b c
	  t: a D b c
 */
 ```
 
 ```cpp
bool isOneEditDistance(string s, string t) {
  const std::size_t s_size(s.size()), t_size(t.size());

  if (std::max(s_size, t_size) - std::min(s_size, t_size) > 1) return false;
  
  const std::size_t min_size = std::min(s_size, t_size);

  for (std::size_t i = 0; i < min_size; ++i) {
    if (s[i] != t[i]) {
      if (s_size == t_size) {
        // s has the same length as t, so the only possibility is replacing one char in s and t
        return s.substr(i + 1) == t.substr(i + 1);
      } else if (s_size > t_size) {
        // s is longer than t, so the only possibility is deleting one char from s
        return s.substr(i + 1) == t.substr(i);
      } else { 
       // t is longer than s, so the only possibility is deleting one char from t
        return s.substr(i) == t.substr(i + 1);
      }
    }
  }

  return std::max(s_size, t_size) - std::min(s_size, t_size) == 1;
}

void UnitTest() {
  assert(isOneEditDistance("geeks", "geeks") == false);
  assert(isOneEditDistance("geeks", "gees") == true);
  assert(isOneEditDistance("geeks", "geks") == true);
  assert(isOneEditDistance("geeks", "geksd") == false);
}

 ```
