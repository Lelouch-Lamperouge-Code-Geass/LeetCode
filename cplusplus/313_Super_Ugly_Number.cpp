class Solution {
public:
  int nthSuperUglyNumber(int n, vector<int>& primes) {
    int primes_size(primes.size());
    vector<int> index(primes_size,0), ugly(n,INT_MAX);
    ugly[0] = 1;
    for (int i=1;i<n;++i) {
      for (int j=0;j<primes_size;++j) ugly[i] = std::min(ugly[i],primes[j]*ugly[index[j]]);
      for (int j=0;j<primes_size;++j) index[j]+=(ugly[i]==ugly[index[j]]*primes[j]? 1 : 0);
    }
    return ugly[n-1];
  }
};
