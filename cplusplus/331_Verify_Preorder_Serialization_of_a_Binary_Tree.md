One way to serialize a binary tree is to use pre-order traversal. When we encounter a non-null node, we record the node's value. If it is a null node, we record using a sentinel value such as #.

```
     _9_
    /   \
   3     2
  / \   / \
 4   1  #  6
/ \ / \   / \
# # # #   # #

```

For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.

Given a string of comma separated values, verify whether it is a correct preorder traversal serialization of a binary tree. Find an algorithm without reconstructing the tree.

Each comma separated value in the string must be either an integer or a character '#' representing null pointer.

You may assume that the input format is always valid, for example it could never contain two consecutive commas such as "1,,3".
  
Example 1:

```
"9,3,4,#,#,1,#,#,2,#,6,#,#"
Return true
```

Example 2:

```
"1,#"
Return false
```

Example 3:

```
"9,#,#,1"
Return false
```

# Solution


### Sollution 1

 When you iterate through the preorder traversal string, for each char:
 * case 1: you see a number c, means you begin to expand a new tree rooted with c, you push it to stack
 * case 2.1: you see a #, while top of stack is a number, you know this # is a left null child, 
             put it there as a mark for next coming node k to know it is being the right child.
 * case 2.2: you see a #, while top of stack is #, you know you meet this # as right null child, 
             you now cancel the sub tree (rooted as t, for example) with these two-# children. 
             But wait, after the cancellation, you continue to check top of stack is whether # or a number:
      * if a number, say u, you know you just cancelled a node t which is left child of u. 
        You need to leave a # mark to the top of stack. So that the next node know it is a right child.
      * if a #, you know you just cancelled a tree whose root, t, is the right child of u. 
        So you continue to cancel sub tree of u, and the process goes on and on.


```cpp
class Solution {
public:
  bool isValidSerialization(string preorder) {
    std::stack<std::string> tokens;
    std::istringstream iss(preorder);
    std::string token("");
    while (std::getline(iss,token,',')){
      if (token != "#") {
        tokens.push(token);
      } else {
        // token=="#"
        while ( !tokens.empty() && tokens.top()=="#" ) {
          tokens.pop();
          if (tokens.empty()) return false;
          tokens.pop(); // pop the number 
        }
        tokens.push("#");
      }
    }
        
    return tokens.size()==1 && tokens.top()=="#";
  }
};
```

Different style.

```cpp
class Solution {
public:
    bool isValidSerialization(string preorder) {
        vector<string> nodes;
        string temp("");
        istringstream iss(preorder);
        while (std::getline(iss, temp, ',')) {
            if (temp == "#") {
              while (!nodes.empty() && nodes.back() == "#") {
                  nodes.pop_back();
                  if (nodes.empty() || nodes.back() == "#") return false; // empty or not a number
                  nodes.pop_back();
              }  
            }
            
            nodes.emplace_back(temp);
        }
        
        return nodes.size() == 1 && nodes.back() == "#";
    }
};
```

### Solution 2

If we treat null's as leaves, then the binary tree will always be full. A full binary tree has a good property that # of leaves = # of nonleaves + 1. Since we are given a pre-order serialization, we just need to find the shortest prefix of the serialization sequence satisfying the property above. If such prefix does not exist, then the serialization is definitely invalid; otherwise, the serialization is valid if and only if the prefix is the entire sequence.

In a binary tree, if we consider null as leaves, then

* all non-null node provides 2 outdegree and 1 indegree (2 children and 1 parent), except root  
* all null node provides 0 outdegree and 1 indegree (0 child and 1 parent).  

Suppose we try to build this tree. During building, we record the difference between out degree and in degree ```diff = outdegree - indegree```. When the next node comes, we then decrease diff by 1, because the node provides an in degree. If the node is not null, we increase diff by 2, because it provides two out degrees. If a serialization is correct, diff should never be negative and diff will be zero when finished.




```cpp
class Solution {
public:
  bool isValidSerialization(string preorder) {
    std::stack<std::string> tokens;
    std::istringstream iss(preorder);
    std::string token("");
    int diff = 1 ;
    while (std::getline(iss,token,',')){
      if (--diff<0) return false;
      if (token!="#") diff += 2;
    }

    return diff == 0;
  }
};
```
