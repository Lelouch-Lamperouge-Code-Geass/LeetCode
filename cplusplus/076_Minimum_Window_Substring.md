Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.


# Solution
```cpp
class Solution {
public:
  string minWindow(string s, string t) {
    vector<int> counter(256,0);
    for (char c : t) {
      ++ counter[c];
    }

    int start(0),min_start(0),min_len(INT_MAX),count(t.size());
    for (int i=0;i<s.size();++i) {
      if(counter[s[i]] > 0) --count; // the char we need
      -- counter[s[i]];
      while (count==0) { //all chars have been found
        int cur_len = i-start+1;
        if (cur_len < min_len) {
          min_start = start;
          min_len = cur_len;
        }
        // begin increase start
        if (counter[s[start]]==0) {
          ++ count;
        }
        ++ counter[s[start]];
        ++ start;
      }
    }
    return min_len==INT_MAX? "" : s.substr(min_start,min_len);
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

