Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.

Note: The input string may contain letters other than the parentheses ( and ).
  
Examples:

```
"()())()" -> ["()()()", "(())()"]
"(a)())()" -> ["(a)()()", "(a())()"]
")(" -> [""] 
```

# Solution


### Solution one
We all know how to check a string of parentheses is valid using a stack. Or even simpler use a counter.
The counter will increase when it is '(' and decrease when it is ')'. Whenever the counter is negative, we have more ')' than '(' in the prefix.

To make the prefix valid, we need to remove a ')'. The problem is: which one? The answer is any one in the prefix. However, if we remove any one, we will generate duplicate results, for example: s = ()), we can remove s[1] or s[2] but the result is the same (). Thus, we restrict ourself to remove the first ) in a series of concecutive )s.

After the removal, the prefix is then valid. We then call the function recursively to solve the rest of the string. However, we need to keep another information: the last removal position. If we do not have this position, we will generate duplicate by removing two ‘)’ in two steps only with a different order.
For this, we keep tracking the last removal position and only remove ‘)’ after that.

Now one may ask. What about '('? What if s = "(()(()" in which we need remove '('?
The answer is: do the same from right to left.
However a cleverer idea is: reverse the string and reuse the code!

```cpp
class Solution {
private:
    void removeInvalidParenthesesWithDFS(vector<string> &result,
                                         const string &s,
                                         int pos,
                                         int last_remove_pos,
                                         const pair<char, char> &parentheses ) {
        int left_paren_count(0);
        for (int i = pos, n = s.size(); i < n; ++i) {
            if (s[i] == parentheses.first) {
                ++ left_paren_count;
            } else if (s[i] == parentheses.second) {
                if (left_paren_count > 0) {
                    -- left_paren_count;
                } else { // more ')' than '('
                    // Right now during the segment [last_remove_pos, pos],
                    // we have need to remove one ')'.
                    // For example, "()())" here our pos is 4, and we can remove one ')'
                    // at index 1, 3, 4. However, remove 3 or 4 will generate duplicates.
                    // Therefore, for consecutive )) we only remove the first one.
                    for (int j = last_remove_pos; j <= i; ++j) {
                        if (s[j] == parentheses.second 
                            && (j == last_remove_pos || s[j - 1] != parentheses.second)) {
                            // Here we remove one char, but it doesn't affect us to decide 
                            // the pos and last_revemo_pos using by the new string.
                            removeInvalidParenthesesWithDFS(result, s.substr(0, j) + s.substr(j + 1), i, j, parentheses );
                        }
                    }
                    
                    // Here we have tried to remove all the possible invalid (
                    return;
                }
            }
        }
        
        // When i == s.size(), we will be here.
        // This means that we have complete removing invalid parentheses from one direction.
        // It could be from left to right, or from right to left.

        if (parentheses.first == '(') {
            // Means it is time to reverse string and process it backwards.
            std::string rs(s);
            std::reverse(rs.begin(), rs.end());
            removeInvalidParenthesesWithDFS(result, rs, 0, 0, std::make_pair(')', '('));
        }
        else {
            // Alreay processed this string from both direction.
            // Previously, we reversed the string and processed it.
            // Need to reverse back.
            result.push_back(std::string(s.rbegin(), s.rend()));
        }
    }
    
public:
    vector<string> removeInvalidParentheses(string s) {
        std::vector<std::string> result;
        removeInvalidParenthesesWithDFS(result, s, 0, 0, std::make_pair('(', ')'));
        return result;
    }
};
```


A different style.

```cpp
class Solution {
public:
    vector<string> removeInvalidParentheses(string s)
    {
        std::vector<std::string> result;
        remove(s, result, 0, 0, std::make_pair('(', ')'));
        return result;
    }

private:
    void remove(const string& s,
        vector<string>& result,
        int last_segment_begin,
        int last_segment_end,
        const std::pair<char, char>& parens)
    {
        for (int stack = 0, i = last_segment_end; i < s.size(); ++i) {
            if (s[i] == parens.first)
                ++stack;
            if (s[i] == parens.second)
                --stack;
            if (stack < 0) { // stack < 0, which means we have more ) than (
                for (int j = last_segment_begin; j <= i; ++j) {
                    if (s[j] == parens.second && (j == last_segment_begin || s[j - 1] != parens.second)) {
                        remove(s.substr(0, j) + s.substr(j + 1), result, j, i, parens);
                    }
                }
                // Here we have tried to remove all the possible invalid (
                return;
            }
        }
        // When i == s.size(), we will be here.

        std::string rs(s);
        std::reverse(rs.begin(), rs.end());

        if (parens.first == '(') {
            // Means it is time to reverse string and process it backwards.
            remove(rs, result, 0, 0, std::make_pair(')', '('));
        }
        else {
            // Alreay processed this string from both direction.
            result.push_back(rs);
        }
    }
};
```

### Solution two

As long as we know how many invalid left parentheses and how many invalid right parentheses then this problem
becomes quite similar to LeetCode-22(generate parentheses). Our primary job is to guarantee the generated string is valid.

```cpp
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        const std::pair<std::size_t, std::size_t> &invalid_count = get_invalid_count(s);
        std::unordered_set<string> reval; // use hashset to remove duplicate
        string temp("");
        removeWithDFS(reval, temp, s, 0, 0, invalid_count.first, invalid_count.second);
        return std::vector<std::string>(reval.begin(), reval.end());
    }
    
    
private:
    // return pair <invalid_left, invalid_right>
    std::pair<std::size_t, std::size_t> get_invalid_count(const std::string &s) {
        std::vector<char> parenthesis;
        std::size_t invalid_left(0), invalid_right(0);
        for (char c : s) {
            if (c == '(') {
                ++ invalid_left;
            }
            
            if (c == ')') {
                if (invalid_left > 0) -- invalid_left;
                else ++ invalid_right;
            }
        }
        
        return std::make_pair(invalid_left, invalid_right);
    }
    
    void removeWithDFS(std::unordered_set<string> &reval, 
                       string &temp, 
                       const std::string &s,
                       std::size_t pos,
                       std::size_t open_pair,
                       std::size_t invalid_left, 
                       std::size_t invalid_right ) {
        if (pos == s.size()) {
            if (invalid_left == 0 && invalid_right == 0 && open_pair == 0) {
                reval.insert(temp);
            }
        } else if (s[pos]!='(' && s[pos]!=')'){
            temp.push_back(s[pos]);
            removeWithDFS(reval, temp, s, pos + 1, open_pair, invalid_left, invalid_right);
            temp.pop_back();
        } else {
            if (s[pos] == '(') {
                // keep this '('
                temp.push_back('(');
                removeWithDFS(reval, temp, s, pos + 1, open_pair + 1, invalid_left, invalid_right);
                temp.pop_back();
                
                // ignore this '('
                if (invalid_left > 0) {
                    removeWithDFS(reval, temp, s, pos + 1, open_pair, invalid_left - 1, invalid_right);
                }
            } else  { // s[pos] == ')'
                // keep this ')'
                if (open_pair > 0) { // we need make sure have open (
                    temp.push_back(')');
                    removeWithDFS(reval, temp, s, pos + 1, open_pair - 1, invalid_left, invalid_right);
                    temp.pop_back();
                }
                
                // ignore this ')'
                if (invalid_right > 0) {
                    removeWithDFS(reval, temp, s, pos + 1, open_pair, invalid_left, invalid_right - 1);
                }
            }
        }
    }
};
```
