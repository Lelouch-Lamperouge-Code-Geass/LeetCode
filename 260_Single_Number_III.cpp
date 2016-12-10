class Solution {
public:

  /*The two numbers that appear only once must differ at some bit, 
    this is how we can distinguish between them. Otherwise, they will be one of the duplicate numbers.

Let’s say the at the ith bit, the two desired numbers differ from each other. which means one number has bit i equaling: 0, the other number has bit i equaling 1.

Thus, all the numbers can be partitioned into two groups according to their bits at location i. the first group consists of all numbers whose bits at i is 0. the second group consists of all numbers whose bits at i is 1.

Notice that, if a duplicate number has bit i as 0, then, two copies of it will belong to the first group. Similarly, if a duplicate number has bit i as 1, then, two copies of it will belong to the second group.

by XoRing all numbers in the first group, we can get the first number. by XoRing all numbers in the second group, we can get the second number.*/
  vector<int> singleNumber(vector<int>& nums) {
    // Pass 1 :
    // Get the XOR of the two numbers we need to find
    int diff = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
    // Get its rightmost set bit
    diff &= -diff;

    // Pass 2 :
    vector<int> rets = {0, 0}; // this vector stores the two numbers we will return
    for (int num : nums)
      {
        if ((num & diff) == 0) // the bit is not set
          {
            rets[0] ^= num;
          }
        else // the bit is set
          {
            rets[1] ^= num;
          }
      }
    return rets;
  }
};
