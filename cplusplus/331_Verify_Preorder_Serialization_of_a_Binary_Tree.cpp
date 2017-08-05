/***
Sollution 1:
// when you iterate through the preorder traversal string, for each char:
// case 1: you see a number c, means you begin to expand a new tree rooted with c, you push it to stack
// case 2.1: you see a #, while top of stack is a number, you know this # is a left null child, 
             put it there as a mark for next coming node k to know it is being the right child.
// case 2.2: you see a #, while top of stack is #, you know you meet this # as right null child, 
             you now cancel the sub tree (rooted as t, for example) with these two-# children. 
             But wait, after the cancellation, you continue to check top of stack is whether # or a number:
// ---- if a number, say u, you know you just cancelled a node t which is left child of u. 
        You need to leave a # mark to the top of stack. So that the next node know it is a right child.
// ---- if a #, you know you just cancelled a tree whose root, t, is the right child of u. 
        So you continue to cancel sub tree of u, and the process goes on and on.

 ***/
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

/*
Some used stack. Some used the depth of a stack. Here I use a different perspective. In a binary tree, if we consider null as leaves, then

all non-null node provides 2 outdegree and 1 indegree (2 children and 1 parent), except root
all null node provides 0 outdegree and 1 indegree (0 child and 1 parent).
Suppose we try to build this tree. During building, we record the difference between out degree and in degree diff = outdegree - indegree. When the next node comes, we then decrease diff by 1, because the node provides an in degree. If the node is not null, we increase diff by 2, because it provides two out degrees. If a serialization is correct, diff should never be negative and diff will be zero when finished.
*/

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
