Given an absolute path for a file (Unix-style), simplify it.

For example,
```
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
```

Corner Cases:
* Did you consider the case where path = "/../"? In this case, you should return "/".
* Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
  In this case, you should ignore redundant slashes and return "/home/foo".

# Solution
```cpp
class Solution {
public:
    string simplifyPath(string path) {
        istringstream iss(path);
        vector<string> items;
        string temp("");
        
        while (std::getline(iss, temp, '/')) {
            if (temp == "." || temp.empty()) {
                continue;
            } else if (temp == "..") {
                if (!items.empty()) items.pop_back();
            } else {
                items.emplace_back(temp);
            }
        }
        
        if (items.empty()) return "/";
        
        ostringstream oss; 
        for (const string &item : items) {
            oss << '/' << item;
        }
        
        return oss.str();
    }
};
```
