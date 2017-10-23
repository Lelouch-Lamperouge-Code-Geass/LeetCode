Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

# Solution

### Solution one


Let's define buy[i] means the max profit for all the transactions within [0,i] whose last trading operation is BUY.  
Example, if i == 2, then the transaction can be [rest, buy], [buy, rest](rest is not trading operation).  
Therefore, it is the max value between  

1. Won't buy stock at i-th day : buy[i-1] , max profit for all the transactions within [0, i-1], 
    whose last trading operation is BUY.
2. Buy stock at i-th day : sell[i-1] - prices[i], sell[i-1] means max profit for all the transactions 
    within [0, i-1], whose last trading operation is SELL.
        
Same for sell[i].

__Note how similar this solution is to LeetCode 121.__

```cpp
class Solution {
public:
  int maxProfit(vector<int>& prices) {
    if (prices.empty()) return 0;

    const std::size_t prices_size(prices.size());
    std::vector<int> buy(prices_size, 0);
    std::vector<int> sell(prices_size, 0);

    buy[0] = - prices[0];
    for (std::size_t i = 1; i < prices_size; ++i) {
      buy[i] = std::max(buy[i-1], sell[i-1] - prices[i]);
      sell[i] = std::max(sell[i-1], buy[i-1] + prices[i]);
    }

    return sell[prices_size - 1];
  }
};
```

We can optimize above solution to O(1) space complexity.

```cpp
class Solution {
public:
  int maxProfit(vector<int>& prices) {
    if (prices.empty()) return 0;

    const std::size_t prices_size(prices.size());
    int pre_buy = - prices[0], pre_sell(0);
    for (std::size_t i = 1; i < prices_size; ++i) {
      pre_buy = std::max(pre_buy, pre_sell - prices[i]);
      pre_sell = std::max(pre_buy + prices[i], pre_sell);
    }

    return pre_sell;
  }
};
```

### Solution two

```cpp
class Solution {
public:
  int maxProfit(vector<int>& prices) {
    int max_profit(0);
    for(std::size_t i=1;i<prices.size();++i){
      max_profit += std::max(0,prices[i]-prices[i-1]);
    }
    return max_profit;
  }
};
```
