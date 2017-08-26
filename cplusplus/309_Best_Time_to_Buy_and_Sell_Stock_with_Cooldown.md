Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times) with the following restrictions:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
Example:

prices = [1, 2, 3, 0, 2]
maxProfit = 3
transactions = [buy, sell, cooldown, buy, sell]

# Solution


### Solution 1

The natural states for this problem is the 3 possible transactions : buy, sell, rest. Here rest means no transaction on that day (aka cooldown).

Then the transaction sequences can end with any of these three states.

For each of them we make an array, buy[n], sell[n] and rest[n].
  
* buy[i] means before day i what is the maxProfit for any sequence end with buy.
* sell[i] means before day i what is the maxProfit for any sequence end with sell.
* rest[i] means before day i what is the maxProfit for any sequence end with rest.

  Then we want to deduce the transition functions for buy sell and rest. By definition we have:
```
buy[i]  = max(rest[i-1]-price, buy[i-1]) 
sell[i] = max(buy[i-1]+price, sell[i-1])
rest[i] = max(sell[i-1], buy[i-1], rest[i-1])
```

Where price is the price of day i. All of these are very straightforward. They simply represents :

```
(1) We have to `rest` before we `buy` and 
(2) we have to `buy` before we `sell`
```

One tricky point is how do you make sure you sell before you buy, since from the equations it seems that [buy, rest, buy] is entirely possible.

Well, the answer lies within the fact that buy[i] <= rest[i] which means rest[i] = max(sell[i-1], rest[i-1]). That made sure [buy, rest, buy] is never occurred.

A further observation is that and rest[i] <= sell[i] is also true therefore

```
rest[i] = sell[i-1]
```

Substitute this in to buy[i] we now have 2 functions instead of 3:

```
buy[i] = max(sell[i-2]-price, buy[i-1])
sell[i] = max(buy[i-1]+price, sell[i-1])
```

This is better than 3, but

we can do even better

Since states of day i relies only on i-1 and i-2 we can reduce the O(n) space to O(1). And here we are at our final solution:

```cpp
class Solution {
public:
  int maxProfit(vector<int>& prices) {
    const std::size_t prices_size(prices.size());
    if (prices_size==0) return 0;
    vector<int> buy(prices_size,0),sell(prices_size,0),rest(prices_size,0);
    buy[0] = -prices[0];
    for (std::size_t i=1;i<prices_size;++i) {
      buy[i] = std::max(buy[i-1],rest[i-1]-prices[i]);
      sell[i] = std::max(sell[i-1],buy[i-1]+prices[i]);
      rest[i] = std::max(rest[i-1],std::max(buy[i-1],sell[i-1]));
    }
    return sell[prices_size-1];
  }
};
```

Can be optimized as


```cpp
int maxProfit(vector<int> &prices) {
    int buy(INT_MIN), sell(0), prev_sell(0), prev_buy;
    for (int price : prices) {
        prev_buy = buy;
        buy = max(prev_sell - price, buy);
        prev_sell = sell;
        sell = max(prev_buy + price, sell);
    }
    return sell;
}
```

### Solution two 
State machine
https://discuss.leetcode.com/topic/30680/share-my-dp-solution-by-state-machine-thinking/2

```cpp
class Solution {
public:
  int maxProfit(vector<int>& prices){
    if (prices.size() <= 1) return 0;
    vector<int> s0(prices.size(), 0);
    vector<int> s1(prices.size(), 0);
    vector<int> s2(prices.size(), 0);
    s1[0] = -prices[0];
    s0[0] = 0;
    s2[0] = INT_MIN;
    for (int i = 1; i < prices.size(); i++) {
      s0[i] = max(s0[i - 1], s2[i - 1]);
      s1[i] = max(s1[i - 1], s0[i - 1] - prices[i]);
      s2[i] = s1[i - 1] + prices[i];
    }
    return max(s0[prices.size() - 1], s2[prices.size() - 1]);
  }
};
```
Can be optimized as

```cpp
int maxProfit(vector<int>& prices) {
  int sold = 0, hold = INT_MIN, rest = 0;
  for (int i=0; i<prices.size(); ++i)
    {
      int prvSold = sold;
      sold = hold + prices[i];
      hold = max(hold, rest-prices[i]);
      rest = max(rest, prvSold);
    }
  return max(sold, rest);
}
```
