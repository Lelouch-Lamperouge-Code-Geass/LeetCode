/***
Solution one
Let's define buy_two[i] means the max profit to buy second stock within [0,i]
Therefore, it is the max value between
(1) buy_two[i-1], the max profit to buy second stock within [0,i-1], don't buy at i-th day. 
(2) sell_one[i-1] - prices[i], buy stock at i-th day + the max profit buy the first stock within [0,i]
Same for sell[i]
 ***/

class Solution {
public:
  int maxProfit(vector<int>& prices) {
    if (prices.empty()) return 0;

    const std::size_t prices_size(prices.size());
    std::vector<int> buy_one(prices_size, 0);
    std::vector<int> sell_one(prices_size, 0);
    std::vector<int> buy_two(prices_size, 0);
    std::vector<int> sell_two(prices_size, 0);

    buy_one[0] = buy_two[0] = -prices[0];

    for (std::size_t i = 1; i < prices_size; ++i) {
      buy_one[i] = std::max(buy_one[i-1], -prices[i]);
      sell_one[i] = std::max(sell_one[i-1], buy_one[i-1] + prices[i]);
      buy_two[i] = std::max(buy_two[i-1], sell_one[i-1] - prices[i]);
      sell_two[i] = std::max(sell_two[i-1], buy_two[i-1] + prices[i]);
    }

    return sell_two[prices_size-1];
  }
};

// It can be optimized as
class Solution {
public:
  int maxProfit(vector<int> & prices) {
    int buy_one(INT_MIN),sell_one(0),buy_two(INT_MIN),sell_two(0);
    for (int price : prices) {
      buy_one = std::max(buy_one,0-price);
      sell_one = std::max(sell_one,buy_one+price);
      buy_two = std::max(buy_two,sell_one-price);
      sell_two = std::max(sell_two,buy_two+price);
    }
    return sell_two;
  }
};
