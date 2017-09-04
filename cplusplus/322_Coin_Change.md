You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
```
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)
```

Example 2:
```
coins = [2], amount = 3
return -1.
```

Note:
You may assume that you have an infinite number of each kind of coin.

# Solution

### Solution 1

The idea is very classic dynamic programming: think of the last step we take. Suppose we have already found out the best way to sum up to amount a, then for the last step, we can choose any coin type which gives us a remainder r where r = a-coins[i] for all i's. For every remainder, go through exactly the same process as before until either the remainder is 0 or less than 0 (meaning not a valid solution). With this idea, the only remaining detail is to store the minimum number of coins needed to sum up to r so that we don't need to recompute it over and over again.

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount < 0) return -1;
        
        vector<int> min_coins(amount + 1, INT_MAX);
        min_coins[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (int coin : coins) {
                if (coin <= i) {
                    if (min_coins[i - coin] != INT_MAX) {
                        min_coins[i] = std::min(min_coins[i], min_coins[i - coin] + 1);
                    }
                }
            }
        }
        
        return min_coins[amount] == INT_MAX ? -1 : min_coins[amount];
    }
};
```

This is my initial solution, which has TLE error. Logically it is working, while it yields much worse performance than above solution, because it have much more redundant recalculations.

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount < 0) return -1;
        
        unordered_set<int> coin_set(coins.begin(), coins.end());
        
        vector<int> min_coins(amount + 1, INT_MAX);
        min_coins[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            if (coin_set.count(i) > 0) {
                min_coins[i] = 1;
            } else {
                int left = 1, right = i - 1;
                while (left <= right) {
                    if (min_coins[left] != INT_MAX && min_coins[right] != INT_MAX) {
                        min_coins[i] = std::min(min_coins[i], min_coins[left] + min_coins[right]);
                    }
                    ++ left, -- right;
                }
            }
        }
        
        return min_coins[amount] == INT_MAX ? -1 : min_coins[amount];
    }
};
```
### Solution 2

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        std::sort(coins.begin(),coins.end());
        int result(INT_MAX);
        dfs(coins,coins.size()-1,amount,0,result);
        return result == INT_MAX ? -1 : result;
    }
private:
    void dfs(vector<int>& coins,int index,int amount,int count,int & result){
        if(index<0) return;

        int number = amount / coins[index];
        for(int i= number; i >= 0;i--){
            int remain = amount - coins[index] * i;
            int new_count = count + i;
            if(remain > 0 && new_count < result){
                dfs(coins,index-1,remain,new_count,result);
            } else if(new_count<result){
                result = new_count;
            } else {
                break;
            }
        }
        
    }
};
```
