class Solution {
public:
  int nthUglyNumber(int n) {
    if(n <= 0) return false; // get rid of corner cases
    if(n == 1) return true; // base case
    int i2(0), i3 = (0), i5 = (0); //pointers for 2, 3, 5
    vector<int> vec(n,1);
    for(int i  = 1; i < n ; ++i )
      {
        vec[i] = min(vec[i2]*2,min(vec[i3]*3,vec[i5]*5));
        if(vec[i] == vec[i2]*2) ++i2;
        if(vec[i] == vec[i3]*3) ++i3;
        if(vec[i] == vec[i5]*5) ++i5;
      }
    return vec.back();
  }
};
