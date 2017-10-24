Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
  
# Solution
  

### Solution one
 
```cpp
class Solution {
public:
  // sell[k][i] = MAX(sell[k][i-1], buy[k][i-1] + prices[i]),
  // sell[k][i] means the max profit for transaction combintion whose last trading is SELL k-th stock within i days.
  int maxProfit(int k, vector<int>& prices) {
    if (k<=0 || prices.empty()) return 0;
    const std::size_t prices_size(prices.size());

    if(k > prices_size/2){
      // Under this condition, we can add profit accumulatively
      int sum(0);
      for(int i = 1;i < prices_size;++i){
        sum += std::max(0,prices[i]-prices[i-1]);
      }
      return sum;
    } else {
      vector< vector<int> > buy(k+1,vector<int>(prices_size+1,0)),
        sell(k+1,vector<int>(prices_size+1,0));

      for(int i = 1;i <= k;++i)
        buy[i][0] = INT_MIN;

      for (std::size_t i = 1; i <= prices_size; ++i) {
        for (int j = 1; j <= k; ++j) {
          buy[j][i] = std::max(buy[j][i-1], sell[j-1][i-1] - prices[i-1]);
          sell[j][i] = std::max(sell[j][i-1], buy[j][i] + prices[i-1]);
        }
      }

      return sell[k][prices_size];
    }
  }
};
```

Above solution can be optimized to below code.

You can also think in a different way based on below code. 
  
The max profit of each day, is the maximum value of

1. the max value of do the i-th buy operation that day(it means we have already bought i-1  and sold i-1 times). We store these information in buy[i].
2. the max value of do the i-th sell operation that day(it means we have already bought i  and sold i-1 times). We store these information in sell[i].

  
Here the i rangs from 1 to k.  

```
class Solution {
public:
  int maxProfit(int k, vector<int>& prices) {
    if( k<=0 || prices.empty() ) return 0;
    const int N(prices.size());

    if(k>=N-1){
      // Under this condition, we can add profit accumulatively
      int sum(0);
      for(int i=1;i<N;++i){
        sum += std::max(0,prices[i]-prices[i-1]);
      }
      return sum;
    } else {
      // Dynamic programming
      vector<int> buy(k,INT_MIN), sell(k,INT_MIN);
      for(int price : prices){
        for(int i=0; i<k; ++i){
          buy[i] = std::max(buy[i], (i==0? 0-price : sell[i-1]-price) );
          sell[i] = std::max(sell[i], buy[i] + price);
        }
      }
      return sell[k-1];
    }
  }

};
```
