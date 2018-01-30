You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -, you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move and therefore the other person will be the winner.
Write a function to compute all possible states of the string after one valid move.
For example, given s = "++++", after one move, it may become one of the following states:

```
[
  "--++",
  "+--+",
  "++--"
]
```

If there is no valid move, return an empty list [].

# Solution

The idea is quite straightforward: just traverse s and each time when we see two consecutive+s, convert them to -s and add the resulting string to the final result moves. But remember to recover the string after that.

```cpp
class Solution {
public:
    vector<string> generatePossibleNextMoves(string s) {
        vector<string> result;
        for (int i = 0, n = s.size(); i + 2 <= n; ++i) {
            if (s[i] == '+' && s[i + 1] == '+') {
                s[i] = s[i + 1] = '-';
                result.emplace_back(s);
                s[i] = s[i + 1] = '+'; // revert back
            }
        }
        return result;
    }
};
```
