/*
* Solution 1
*/
class Solution {
public:
  bool isHappy(int n) {
    if (n<=0) return false;
    unordered_set<int> visited;
    visited.insert(n);
    while (n!=1) {
      int sum(0);
      while (n) {
        sum += std::pow(n%10,2);
        n /= 10;
      }
      if (visited.find(sum)!=visited.end()) return false;
      visited.insert(sum);
      n = sum;
    }
    return true;

  }
};


/*
 * Solution 2
 */
class Solution {
public:
  int digitSquareSum(int n) {
    int sum = 0, tmp;
    while (n) {
      tmp = n % 10;
      sum += tmp * tmp;
      n /= 10;
    }
    return sum;
  }

  bool isHappy(int n) {
    int slow, fast;
    slow = fast = n;
    do {
      slow = digitSquareSum(slow);
      fast = digitSquareSum(fast);
      fast = digitSquareSum(fast);
    } while(slow != fast);
    if (slow == 1) return true;
    else return false;
  }


};
