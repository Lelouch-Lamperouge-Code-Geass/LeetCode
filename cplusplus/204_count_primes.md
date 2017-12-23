##### Description:

Count the number of prime numbers less than a non-negative number, n.

# Solution
     
A prime number is a whole number that has exactly two factors, 1 and itself.

In mathematics, the __sieve of Eratosthenes__ is a simple, ancient algorithm for finding all prime numbers up to any given limit.
It does so by iteratively marking as composite (i.e., not prime) the multiples of each prime, starting with the first prime number, 2. The multiples of a given prime are generated as a sequence of numbers starting from that prime, with constant difference between them that is equal to that prime. This is the sieve's key distinction from using trial division to sequentially test each candidate number for divisibility by each prime.


The earliest known reference to the sieve  is in Nicomachus of Gerasa's Introduction to Arithmetic,[3] which describes it and attributes it to Eratosthenes of Cyrene, a Greek mathematician.
     
One of a number of prime number sieves, it is one of the most efficient ways to find all of the smaller primes. It may be used to find primes in arithmetic progressions.  
     
A prime number is a natural number that has exactly two distinct natural number divisors: 1 and itself.
     
To find all the prime numbers less than or equal to a given integer n by Eratosthenes' method:     
     
1. Create a list of consecutive integers from 2 through n: (2, 3, 4, ..., n).  
2. Initially, let p equal 2, the smallest prime number.  
3. Enumerate the multiples of p by counting to n from 2p in increments of p, and mark them in the list (these will be 2p, 3p, 4p, ...; the p itself should not be marked).  
4. Find the first number greater than p in the list that is not marked. If there was no such number, stop. Otherwise, let p now equal this new number (which is the next prime), and repeat from step 3.  
5. When the algorithm terminates, the numbers remaining not marked in the list are all the primes below n.     
     
The main idea here is that every value given to p will be prime, because if it were composite it would be marked as a multiple of some other, smaller prime. Note that some of the numbers may be marked more than once (e.g., 15 will be marked both for 3 and 5).
     
As a refinement, it is sufficient to mark the numbers in step 3 starting from p^2, as all the smaller multiples of p will have already been marked at that point. This means that the algorithm is allowed to terminate in step 4 when p^2 is greater than n.    
     
The sieve of Eratosthenes is a popular way to benchmark computer performance. As can be seen from the above by removing all constant offsets and constant factors and ignoring terms that tend to zero as n approaches infinity, the time complexity of calculating all primes below n in the random access machine model is O(n log log n) operations, a direct consequence of the fact that the prime harmonic series asymptotically approaches log log n. It has an exponential time complexity with regard to input size, though, which makes it a pseudo-polynomial algorithm. The basic algorithm requires O(n) of memory.
     
The bit complexity of the algorithm is O(n (log n) (log log n)) bit operations with a memory requirement of O(n).    
     
https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes     

```cpp
class Solution {
public:
    int countPrimes(int n) {
        std::vector<bool> prime(n, true);
        prime[0] =  prime[1] = false;
        for (int i = 0; i < sqrt(n); ++i) {
            // Whenever we reach prime[i] we already know it is a prime or not
            // based on previous checking.
            // If prime[i] is false, which means it has been marked before,
            // we can skip this.
            if (prime[i]) {
                for (int j = i*i; j < n; j += i) {
                    prime[j] = false;
                }    
            }    
        }
        return std::count(prime.begin(), prime.end(), true);
    }
};
```
