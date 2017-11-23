Given an array of integers, every element appears three times except for one, which appears exactly once. Find that single one.

__Note:__

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

# Solution

As we known, an integer is generally 32-bit or 64-bit. For each bit position, here is the status 0=>1=>2=>0, so we reset it to 0 once the bit position has been hit 3 times. Here we need two status:

1. ones represent the first bit on that position
2. twos represent the second bit on that position

```
hits : 0    1    2    3                 
one  : 0 => 1 => 0 => 0
two  : 0 => 0 => 1 => 0
```

For 'ones', we can get 

```
ones = ones ^ A[i]; if (twos == 1) then ones = 0
```

that can be tansformed to 

```
ones = (ones ^ A[i]) & ~twos
```

Similarly, for 'twos', we can get ```twos = twos ^ A[i]; if (ones == 1) then twos = 0``` and ```twos = (twos ^ A[i]) & ~ones```.

```cpp
int singleNumber(vector<int>& nums) {
  int one(0),two(0);
  for (int num : nums) {
    one = (one ^ num) & ~two;
    two = (two ^ num) & ~one;
  }
  return one;
}
```
