You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -, you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move and therefore the other person will be the winner.

Write a function to determine if the starting player can guarantee a win.

For example, given s = "++++", return true. The starting player can guarantee a win by flipping the middle "++" to become "+--+".

# Solution

### Solution one : Backtracking

The idea is try to replace every "++" in the current string s to "--" and see if the opponent can win or not, if the opponent cannot win, great, we win!

For the time complexity, here is what I thought, let's say the length of the input string s is n, there are at most n - 1 ways to replace "++" to "--" (imagine s is all "+++..."), once we replace one "++", there are at most (n - 2) - 1 ways to do the replacement, it's a little bit like solving the N-Queens problem, the time complexity is (n - 1) x (n - 3) x (n - 5) x ..., so it's O(n!!), double factorial.

```cpp
class Solution {
public:
    bool canWin(string s) {
        for (std::size_t i = 0, n = s.size(); i + 1 < n; ++i) {
            if (s[i] == '+' && s[i+1] == '+') { // Can flip
                string next_s(s);
                next_s[i] = next_s[i+1] = '-';
                if (!canWin(next_s)) {
                    return true;
                }
            }
        }
        
        return false;
    }
};
```

If we use HashMap to memorize both win string & lose string, we can further reduce time from 96ms to 13ms:

```cpp
class Solution {
public:
    bool canWin(string s) {
         // Since the rule won't change here, we can use a static HashMap
        static std::unordered_map<std::string, bool> memoization_table;
        if (memoization_table.count(s) != 0) {
            return memoization_table[s];
        }
        
        for (std::size_t i = 0, n = s.size(); i + 1 < n; ++i) {
            if (s[i] == '+' && s[i+1] == '+') { // Can flip
                string next_s(s);
                next_s[i] = next_s[i+1] = '-';
                if (!canWin(next_s)) {
                    memoization_table[s] = true;
                    return true;
                }
            }
        }
        
        memoization_table[s] = false;
        return false;
    }
};
```
