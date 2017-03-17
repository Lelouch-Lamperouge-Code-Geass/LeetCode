/***
Solution one
Let's define buy[i] means buy the stock at any day between [0,i].
Therefore, it is the max value between
(1) buy[i-1] : buy the stock at any day between [0, i-1]
(2) -prices[i] : buy the stock at i-th day
Same for sell[i]
 ***/

class Solution {
public:
  int maxProfit(vector<int>& prices) {
    if (prices.empty()) return 0;

    const std::size_t prices_size(prices.size());
    std::vector<int> buy(prices_size, 0);
    std::vector<int> sell(prices_size, 0);

    buy[0] = - prices[0];
    for (std::size_t i = 1; i < prices_size; ++i) {
      buy[i] = std::max(buy[i-1], 0 - prices[i]);
      sell[i] = std::max(buy[i-1] + prices[i], sell[i-1]);
    }

    return sell[prices_size - 1];
  }
};

/***
Solution two
If you look at above solutions, it can be optimized.

 ***/
class Solution {
public:
  int maxProfit(vector<int>& prices) {
    int buy1(INT_MIN),sell1(0);
    for(const int price : prices){
      buy1 = std::max(buy1,0-price);
      sell1 = std::max(sell1,buy1+price);
    }
    return sell1;
  }
};


/***
Solution three
 ***/
class Solution {
public:
  int maxProfit(vector<int>& prices) {
    int min_so_far(INT_MAX),reval(0);
    for(std::size_t i=0;i<prices.size();++i){
      reval = std::max(reval,prices[i]-min_so_far);
      min_so_far = std::min(min_so_far,prices[i]);
    }
    return reval;
  }
};

