Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character  
b) Delete a character  
c) Replace a character  

# Solution

This is a classic problem of Dynamic Programming. We define the state dp[i][j] to be the minimum number of operations to convert word1[0..i - 1] to word2[0..j - 1]. The state equations have two cases: the boundary case and the general case. Note that in the above notations, both i and j take values starting from 1.

For the boundary case, that is, to convert a string to an empty string, it is easy to see that the mininum number of operations to convert word1[0..i - 1] to "" requires at least i operations (deletions). In fact, the boundary case is simply:

```
dp[i][0] = i;
dp[0][j] = j
```

Now let's move on to the general case, that is, convert a non-empty word1[0..i - 1] to another non-empty word2[0..j - 1]. Well, let's try to break this problem down into smaller problems (sub-problems). Suppose we have already known how to convert word1[0..i - 2] to word2[0..j - 2], which is dp[i - 1][j - 1]. Now let's consider word[i - 1] and word2[j - 1]. If they are euqal, then no more operation is needed and dp[i][j] = dp[i - 1][j - 1]. Well, what if they are not equal?

If they are not equal, we need to consider three cases:


* Replace word1[i - 1] by word2[j - 1] (dp[i][j] = dp[i - 1][j - 1] + 1 (for replacement));
* Delete word1[i - 1] and word1[0..i - 2] = word2[0..j - 1] (dp[i][j] = dp[i - 1][j] + 1 (for deletion));
* Insert word2[j - 1] to word1[0..i - 1] and word1[0..i - 1] + word2[j - 1] = word2[0..j - 1] (dp[i][j] = dp[i][j - 1] + 1 (for insertion)).


Make sure you understand the subtle differences between the equations for deletion and insertion. For deletion, we are actually converting word1[0..i - 2] to word2[0..j - 1], which costs dp[i - 1][j], and then deleting the word1[i - 1], which costs 1. The case is similar for insertion.

Putting these together, we now have:

```
dp[i][0] = i;
dp[0][j] = j;
dp[i][j] = dp[i - 1][j - 1], if word1[i - 1] = word2[j - 1];
dp[i][j] = min(dp[i - 1][j - 1] + 1, dp[i - 1][j] + 1, dp[i][j - 1] + 1), otherwise.
```
 
The above state equations can be turned into the following code directly.

__Note that you can't check the min of   ```min_distance[i][j-1], min_distance[i-1][j], min_distance[i-1][j-1]```, and then add 1 depends on whether ``` word1[i-1]==word2[j-1]``` or not.__  This is because ```min_distance[i][j-1]``` requires one insertion operation, and min_distance[i-1][j] requires one delete operation, while min_distance[i-1][j-1] may or may need replacement operation is depends on word1[i - 1] equals word2[j - 1] or not.
  
```cpp  
class Solution {
public:
  int minDistance(string word1, string word2) {
    const std::size_t size1(word1.size()),size2(word2.size());
    vector< vector<int> > min_distance (size1+1, vector<int>(size2+1,0) );

    for (std::size_t i=1;i<=size1;++i) min_distance[i][0] = i;
    for (std::size_t i=1;i<=size2;++i) min_distance[0][i] = i;

    for (std::size_t i=1;i<=size1;++i) {
      for (std::size_t j=1;j<=size2;++j) {
        // Delete and insert
        min_distance[i][j] = std::min(min_distance[i][j-1]+1,min_distance[i-1][j]+1);
        // Replacement if word1[i-1]!=word2[j-1].
        min_distance[i][j] = std::min(min_distance[i][j],
                                      word1[i-1]==word2[j-1]? min_distance[i-1][j-1] : min_distance[i-1][j-1]+1);
      }
    }
    return min_distance[size1][size2];
  }
};
```

For this solution, you need to tell why when word1[i-1] == word2[j-1], we can use min_distance[i-1][j-1] directly?
Is it possible that min_distance[i-1][j] is smaller than min_distance[i-1][j-1]?
The answers is NO. Since min_distance[i][j] records the minimal operations to convert strA[0,i-1] to strB[0,j-1], and min_distance[i-1][j] has one more  character than min_distance[i-1][j-1]. 

```cpp
class Solution {
public:
  int minDistance(string word1, string word2) {
    const std::size_t size1(word1.size()),size2(word2.size());
    vector< vector<int> > min_distance (size1+1, vector<int>(size2+1,0) );

    for (std::size_t i=1;i<=size1;++i) min_distance[i][0] = i;
    for (std::size_t i=1;i<=size2;++i) min_distance[0][i] = i;

    for (std::size_t i=1;i<=size1;++i) {
      for (std::size_t j=1;j<=size2;++j) {
        if(word1[i-1] == word2[j-1]) {
          min_distance[i][j] = min_distance[i-1][j-1];
        } else {
          // substring replace
          min_distance[i][j] =std::min( std::min(min_distance[i][j-1] // for insertion
                                                 ,min_distance[i-1][j])  // for delete
                                        ,min_distance[i-1][j-1]); // for replace
          // current operation :delete/replace/insert
          min_distance[i][j] += 1;
        }
      }
    }
    return min_distance[size1][size2];
  }
};
```
