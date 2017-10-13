A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).  

Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.  

For example,

Given low = "50", high = "100", return 3. Because 69, 88, and 96 are three strobogrammatic numbers.  

Note:  
Because the range might be a large number, the low and high numbers are represented as string.  

# Solution

1. Initialize an all-'0' string with length from low.size() to high.size(), e.g. "0000"
2. Use two pointers, left and right position and try to fill left and right with mirror pairs
3. Finally, when left is larger than right, which means that we have filled the whole string. Then we need to make sure 
   the generated string is within range. If it is, increase the count.
   
Note here we don't use the methology like "247 Strobogrammatic Number II", which is building the strings from bottom up, and 
then check the string are within the range or not. This is because there are potentailly many redundant calculations there.

Let's say the "low" string has length == 10, then we need to get length == 10 strings based on length < 10 strings(0 to 9), the time complexity is pretty bad.

```cpp

int strobogrammaticInRange(string low, string high) {
    map<char, char> mp = {{'0', '0'}, {'1', '1'}, {'6', '9'}, {'8', '8'}, {'9', '6'}};
    int count = 0;
    for(int len = low.length(); len <= high.length(); len++) {
        string temp(len, '0'); // Initilize the string with all '0'
        dfs(low, high, temp, 0, len - 1, count, mp);
    }
    return count;
}
void dfs(string low, string high, string str, int left, int right, int &count, map<char, char> &mp) {
    if(left > right) {
        // Make sure generated string are within range
        if((str.length() == low.length() && str.compare(low) < 0) || 
           (str.length() == high.length() && str.compare(high) > 0)) return;
        count++; 
        return;
    }
    // Try to build all possible strobogrammatic number
    for(auto p : mp) {
        str[left] = p.first; 
        str[right] = p.second;
        if(str.size() != 1 && str[0] == '0') continue; // avoid "080",...
        if(left < right || left == right && p.first == p.second) {
          dfs(low, high, str, left + 1, right - 1, count, mp);
        }
    }
}

```
