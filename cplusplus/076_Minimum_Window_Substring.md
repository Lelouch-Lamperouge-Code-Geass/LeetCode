Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

__Note:__

If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.


# Solution

The simplest solution for this problem is : for each index in s, we create a window which ends with that index, and expand the start position of that window backwards until we find a valid window. That valid window is the minimum window in S whcih contains all the characters in T. Then the final result is the minimal window of all the minimal windows ends with each index. The time complexity is obviously O(N^2).

How can we do better?

One observation from above solution is that, when we move from index ```i``` to index ```i + 1```, there is actually only one char changes. If on index ```i``` we don't have a valid window but just one char is missing, and that missing char  is on index ```i+1```. Then on index ```i+1``` we just update the based on the window of index ```i```, and there is no need to create a new window again.

We can reduce these kind of recalculations by using a sliding window.

We use a sliding window and begin expand the end index of that window, in our solution the window end index is ```i``` (you can rename it to ```window_end``` if you want). Once we find a valid window, we begin increase ```window_start```  and check the smaller window is valid or not. If it is valid, compare with our result so far; if it is not valid, which means all the valid window on ```i``` has been considered, and it is time to increase ```i```.

We use char_counter to count the number of each char in t. Whenever we add a char into current window, we decrease its count; whenever we pop a char out of current window, we increase its count. Here two things you need to notice:

* For character which is not in string ```t```, when it is in the window, its count is negative; and when current window does have this character, its count will be 0. Therefore, its count will never be positive.
* It is possible that one character is contained in ```t```, but in current window we have more than we need. But we don't need to worry much about this case, because in that case, its count will be nagative.

Since every char in s goes into and out of the sliding window only once, the time complexity is O(size of s).

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        std::vector<int> char_counter(256, 0);
        
        for (char c : t) {
            ++ char_counter[c];
        }
        
        std::size_t total_chars(t.size()), char_to_find(t.size());
        
        std::size_t window_start(0), min_start(0), min_len(INT_MAX);
        for (std::size_t i = 0, n = s.size(); i < n; ++i) {
            // Add current char into current window
            -- char_counter[s[i]];
            if (char_counter[s[i]] >= 0) {
                -- char_to_find;
            }
            
            while (char_to_find == 0) { // A match window
                std::size_t cur_window_len = i + 1 - window_start;
                if (cur_window_len < min_len) {
                    min_start = window_start;
                    min_len = cur_window_len;
                }
                
                // Pop the char on window_start out of current window.
                ++ char_counter[s[window_start]];
                if (char_counter[s[window_start]] > 0) {
                    // Chars which are not in t, its count will never be positive.
                    // Chars which are in t but if current window has more than we need, 
                    // its count will still be 0 or negative.
                    ++ char_to_find;
                }
                ++ window_start;
            }
        }
        
        return min_len == INT_MAX ? "" : s.substr(min_start, min_len);
    }
};
```  
  
  
Here is a 10-line template that can solve most 'substring' problems
```cpp
string minWindow(string s, string t) {
        vector<int> map(256,0);
        for(auto c: t) map[c]++;
        int counter=t.size(), begin=0, end=0, d=INT_MAX, head=0;
        while(end<s.size()){
            if(map[s[end++]]-->0) counter--; //in t
            while(counter==0){ //valid
                if(end-begin<d)  d=end-(head=begin);
                if(map[s[begin++]]++==0) counter++;  //make it invalid
            }  
        }
        return d==INT_MAX? "":s.substr(head, d);
    }
```

Here comes the template.

For most substring problem, we are given a string and need to find a substring of it which satisfy some restrictions. A general way is to use a hashmap assisted with two pointers. The template is given below.
  
```cpp
int findSubstring(string s){
        vector<int> map(128,0);
        int counter; // check whether the substring is valid
        int begin=0, end=0; //two pointers, one point to tail and one  head
        int d; //the length of substring

        for() { /* initialize the hash map here */ }

        while(end<s.size()){

            if(map[s[end++]]-- ?){  /* modify counter here */ }

            while(/* counter condition */){ 
                 
                 /* update d here if finding minimum*/

                //increase begin to make it invalid/valid again
                
                if(map[s[begin++]]++ ?){ /*modify counter here*/ }
            }  

            /* update d here if finding maximum*/
        }
        return d;
  }
```

One thing needs to be mentioned is that when asked to find maximum substring, we should update maximum after the inner while loop to guarantee that the substring is valid. On the other hand, when asked to find minimum substring, we should update minimum inside the inner while loop.

The code of solving Longest Substring with At Most Two Distinct Characters is below:


```cpp
int lengthOfLongestSubstring(string s) {
        vector<int> map(128,0);
        int counter=0, begin=0, end=0, d=0; 
        while(end<s.size()){
            if(map[s[end++]]++>0) counter++; 
            while(counter>0) if(map[s[begin++]]-->1) counter--;
            d=max(d, end-begin); //while valid, update d
        }
        return d;
    }
```    

