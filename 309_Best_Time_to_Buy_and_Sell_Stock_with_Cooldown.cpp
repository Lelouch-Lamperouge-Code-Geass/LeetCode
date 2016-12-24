/*
Solution 1:
buy[i] means before day i what is the maxProfit for any sequence end with buy.
sell[i] means before day i what is the maxProfit for any sequence end with sell.
rest[i] means before day i what is the maxProfit for any sequence end with rest.

buy[i] compare to buy[i-1] is because the definition of buy[i] is the maxProfit of ALL sequences end with buy BEFORE i.
For example
prices = [1,5,3,4]
buy[0] = -1 max of [buy]
buy[1] = -1 max of [buy,rest], [rest, buy]
buy[2] = -1 max of [buy,rest,rest], [rest, buy,rest], [rest, rest, buy]
buy[3] = 0 max of [buy,rest,rest,rest], [rest, buy,rest,rest], [rest, rest, buy,rest], 
                   [rest, rest, rest, buy], [buy, sell, rest, buy]
*/
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
