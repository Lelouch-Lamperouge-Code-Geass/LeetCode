You have n super washing machines on a line. Initially, each washing machine has some dresses or is empty.

For each move, you could choose any m (1 ≤ m ≤ n) washing machines, and pass __one dress__ of __each washing machine__ to one of its adjacent washing machines at the same time .

Given an integer array representing the number of dresses in each washing machine from left to right on the line, you should find the __minimum number of moves__ to make all the washing machines have the same number of dresses. If it is not possible to do it, return -1.

##### Example1

```
Input: [1,0,5]

Output: 3

Explanation: 
1st move:    1     0 <-- 5    =>    1     1     4
2nd move:    1 <-- 1 <-- 4    =>    2     1     3    
3rd move:    2     1 <-- 3    =>    2     2     2   
```

##### Example2

```
Input: [0,3,0]

Output: 2

Explanation: 
1st move:    0 <-- 3     0    =>    1     2     0    
2nd move:    1     2 --> 0    =>    1     1     1     
```

##### Example3

```
Input: [0,2,0]

Output: -1

Explanation: 
It's impossible to make all the three washing machines have the same number of dresses.
```

##### Note:

* The range of n is [1, 10000].
* The range of dresses number in a super washing machine is [0, 1e5].

# Solution

First we check the sum of dresses in all machines. if that number cannot be divided by count of machines, there is no solution.

Otherwise, we can always transfer a dress from one machine to another, one at a time until every machines reach the same number, so there must be a solution. In this way, the total actions is sum of operations on every machine.

Since we can operate several machines at the same time, the minium number of moves is the maximum number of necessary operations on every machine.

For a single machine, necessary operations is to transfer dresses from one side to another until sum of both sides and itself reaches the average number. 

For example, for input [1,0,5], we know that evetually each washing machine should have 2 dresses.

And the operation array is initially [-1, -2, 3], which means washing machine 1 need add one dress, washing machine 2 need add two dresses, and wahing machine 3 need give out 3 dresses. Or in other words, washing machine 1 need one ADD operation, washing machine 2 need two ADD operations, and washing machine 3 need performe three GIVEAWAY operation.

> Note that for the operation array, the number of GIVEAWAY operation is the same as the number of ADD operation, these two kinds operation basically neutralize each other. For example, for operation array [-1, 1], one ADD operation and one GIVEAWAY operation is needed and they paired up as one "move".

Let's continue with our example with initial operation array [-1, -2, 3], we know that in order to add one address to waching machine 1 we need one GIVEAWAY opertaion on machine 2. If current operation number on washing machine two is positive, which means right now washing machine 2 only need perform GIVEAWAY operation, we add -1 on the operation number to neutralize it; however if it is negative, which means washing machine 2 also need perform ADD operation too, we can also add the -1 on the operation number, but here it means washing machine 2 need to get dresses from other washing machines.

The work flow like this:

```
[-1, -2, 3]  : basically means [1 ADD, 2 ADD, 3 GIVEAWAY] 

[0, -3, 3] : we add the operations of washing machine 1 on washing machine 2

[0, 0, 0] : we add the operations of washing machine 2 on washing machine 3

Done.
```

```cpp
class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        if (machines.empty()) return 0;
       
        long total_dresses = std::accumulate(machines.begin(), machines.end(), 0);
            
        const std::size_t num_of_machine = machines.size();
        if (total_dresses % num_of_machine != 0) return -1;
        int average_dress_per_machine = total_dresses / num_of_machine;
        
        int operation_load(0), reval(0);
        
        for (int dress_on_this_machine : machines) {
            int curr_operation = dress_on_this_machine - average_dress_per_machine;
            operation_load = curr_operation + operation_load;
            
            reval = std::max(reval, curr_operation);
            reval = std::max(reval, std::abs(operation_load));
        }
        
        return reval;
    }
};
```











