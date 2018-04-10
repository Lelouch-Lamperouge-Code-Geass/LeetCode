Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
  
# Solution  

### Solution one
  
Let's define buy_two[i] means the max profit to buy second stock within [0,i]

Therefore, it is the max value between

1. buy_two[i-1], the max profit to buy second stock within [0,i-1], don't buy at i-th day. 
2. sell_one[i-1] - prices[i], buy stock at i-th day + the max profit buy the first stock within [0,i]

Same for sell[i]

__Why not let buy_two[i] means "the max profit to buy second stock on day i"?__

Let's see if we define it like this, then the value of ```buy_two[i] = Max{sell_one[k], k from 0 to i-1} - prices[i]```, because sell_one means "the max profit to sell one stock on day i"! This is hard to track.  

Another example is that the maximum profit of selling first stock on day i is depends on "maximum profit of buying first stock from day 0 to day i - 1".  Therefore, we can't define like this.

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        
        const std::size_t n = prices.size();
        
        vector<int> buy_one(n, INT_MIN), sell_one(n, 0), buy_two(n, INT_MIN), sell_two(n, 0);
        buy_one[0] = -prices[0];
        buy_two[0] = -prices[0];
        
        for (std::size_t i = 1; i < n; ++i) {
            buy_one[i] = std::max(buy_one[i-1], 0 - prices[i]);
            sell_one[i] = std::max(sell_one[i-1], buy_one[i-1] + prices[i]);
            buy_two[i] = std::max(buy_two[i-1], sell_one[i] - prices[i]);
            sell_two[i] = std::max(sell_two[i-1], buy_two[i-1] + prices[i]);
        }
        
        return sell_two[n - 1];
    }
};
```

The above solution can be optimized to O(1) space complexity.

You can also consider below solution simulate a state transition.

The max profit of any day, is depend on the status of

1. The maximum if we've just buy  1st stock so far. 
2. The maximum if we've just sold 1nd stock so far.
3. The maximum if we've just buy  2nd stock so far.
4. The maximum if we've just sold 2nd stock so far.

We only need these four information to choose the optimal operation.

In summary, our maximum profix is depend on "maximum profit of each day". And maximum profit of each day is depend on :

1. The maximum if we've just buy  1st stock so far. 
2. The maximum if we've just sold 1nd stock so far.
3. The maximum if we've just buy  2nd stock so far.
4. The maximum if we've just sold 2nd stock so far.

```cpp
class Solution {
public:
  int maxProfit(vector<int> & prices) {
    int buy_one(INT_MIN),sell_one(0),buy_two(INT_MIN),sell_two(0);
    for (int price : prices) {
      buy_one = std::max(buy_one,0-price); // The maximum if we've just buy  1st stock so far. 
      sell_one = std::max(sell_one,buy_one+price);  // The maximum if we've just sold 1nd stock so far.
      buy_two = std::max(buy_two,sell_one-price); // The maximum if we've just buy  2nd stock so far.
      sell_two = std::max(sell_two,buy_two+price); // The maximum if we've just sold 2nd stock so far.
    }
    return sell_two;
  }
};
```
