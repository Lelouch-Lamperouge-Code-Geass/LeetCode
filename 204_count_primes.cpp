class Solution {
public:
     
    int countPrimes(int n) {
    	if (n<2) return 0; // prime begin at 2
    	vector<bool> is_prime(n,true);
    	is_prime[0] = is_prime[1] = false;
    	for (int i=2;i*i<n;++i) {
    		if(!is_prime[i]) continue;
    		for (int j=i;i*j<n;++j) {
    			is_prime[i*j] = false;
    		}
    	}
    	return std::count(is_prime.begin(),is_prime.end(),true);
    }
};
