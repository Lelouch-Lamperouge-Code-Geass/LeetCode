Given a string which contains only lowercase letters, remove duplicate letters so that every letter appear once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Example:
Given "bcabc"
Return "abc"

Given "cbacdcbc"
Return "acdb"

# Solution

First, given "bcabc", the solution should be "abc". If we think about this problem intuitively, you would sort of go from the beginning of the string and start removing one if there is still the same character left and a smaller character is after it. Given "bcabc", when you see a 'b', keep it and continue with the search, then keep the following 'c', then we see an 'a'. Now we get a chance to get a smaller lexi order, you can check if after 'a', there is still 'b' and 'c' or not. We indeed have them and "abc" will be our result.

Come to the implementation, we need some data structure to store the previous characters 'b' and 'c', and we need to compare the current character with previous saved ones, and if there are multiple same characters, we prefer left ones. This calls for a stack.

After we decided to use stack, the implementation becomes clearer. From the intuition, we know that we need to know if there are still remaining characters left or not. So we need to iterate the array and save how many each characters are there. A visited array is also required since we want unique character in the solution. The line while(!stack.isEmpty() && stack.peek() > c && count[stack.peek()-'a'] > 0) checks that the queued character should be removed or not, like the 'b' and 'c' in the previous example. After removing the previous characters, push in the new char and mark the visited array.

__Time complexity: O(n), n is the number of chars in string.__

__Space complexity: O(n) worst case.__
  
```cpp
// We need to keep the monotically decreasing substring that contains all the char in the s. 
// So we just use a vector to mimic the stack!
class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> remain_count(256, 0);
        vector<bool> added_to_result(256, false);
        for (char c : s)
            ++ remain_count[c];
        
        /** the key idea is to keep a monotically increasing sequence **/
        string result("");
        
        for (char c : s) {
            -- remain_count[c];
            if (added_to_result[c]) continue;
            while (!result.empty() && c < result.back() && remain_count[result.back()] > 0) {
                // As long as current char is smaller than the last char of current result
                // and the last char of result will appear later, we can safely pop the last char out
                added_to_result[result.back()] = false;
                result.pop_back();
            }
            result.push_back(c);
            added_to_result[c] = true;
        }
        return result;
    }
};
```
