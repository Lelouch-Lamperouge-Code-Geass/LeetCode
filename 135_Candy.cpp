// Copyright (C) 2016 by yangliu

int candy(vector<int>& ratings) {

  const int n (ratings.size());

  // everyone has at least one candy
  vector<int> candies(n,1);

  // left to right, make sure higher rating has 1 more candy
  // than its left neighbor
  for (int i=1;i<n;++i) {
    if (ratings[i] > ratings[i-1])
      candies[i] = 1+candies[i-1];
  }

  // right to left, make sure higher rating has 1 more candy
  // than its right neighbor. Make sure it doesn't make candies
  // less.
  for (int i=n-2;i>=0;--i) {
    if (ratings[i] > ratings[i+1])
      candies[i] = std::max(candies[i],1+candies[i+1]);
  }

  // right now child with higher rating has more candies than
  // get total candies
  int res = std::accumulate(candies.begin(),candies.end(),0);

  return res;
}
