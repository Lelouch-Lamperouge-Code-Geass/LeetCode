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

Notice that below two solutions are essentailly the same just from different perspective, please check their difference.

__The key point is to realize that we can add maximum two dress on a machine(adding one from left neighbor and one from right neighbor), but can give away maximum one dress on a machine.__


### Solution if we think from operation perspective

First we check the sum of dresses in all machines. if that number cannot be divided by count of machines, there is no solution.

Otherwise, we can always transfer a dress from one machine to another, one at a time until every machines reach the same number, so there must be a solution. In this way, the total actions is sum of operations on every machine.

__Since we can operate several machines at the same time, the minium number of moves is the maximum number of necessary operations on every machine.__

For a single machine, necessary operations is to transfer dresses from one side to another until sum of both sides and itself reaches the average number. 


For example, for input [1,0,5], we know that evetually each washing machine should have 2 dresses.

And the operation array is initially [+1, +2, -3], which means washing machine 1 need add one dress, washing machine 2 need add two dresses, and washing machine 3 need give out 3 dresses. Or in other words, washing machine 1 need one ADD operation, washing machine 2 need two ADD operations, and washing machine 3 need performe three GIVEAWAY operation.

> Note that for the operation array, the number of GIVEAWAY operation is the same as the number of ADD operation, these two kinds operation basically neutralize each other. For example, for operation array [-1, +1], one ADD operation and one GIVEAWAY operation is needed and they paired up as one "move".

Let's continue with our example with initial operation array [+1, +2, -3], we know that in order to add one address to waching machine 1 we need one GIVEAWAY opertaion on machine 2. If current operation number on washing machine two is positive, which means right now washing machine 2 only need perform GIVEAWAY operation, we add +1 on the operation number to neutralize it; however if it is negative, which means washing machine 2 also need perform ADD operation too, we can also add the -1 on the operation number, but here it means washing machine 2 need to get dresses from other washing machines.

The work flow like this:

```
[+1, +2, -3]  : basically means [1 ADD, 2 ADD, 3 GIVEAWAY] 

[0, +3, -3] : we add the operations of washing machine 1 on washing machine 2

[0, 0, 0] : we add the operations of washing machine 2 on washing machine 3

Done.
```

Let me use an example to briefly explain this. For example, your machines is ```[0,0,11,5]```. So your total is 16 and the target value for each machine is 4. Convert the machines array to a kind of gain/lose array, we get: [+4,+4,-7,-1]. Now what we want to do is go from the first one and try to make all of them 0.

To make the 1st machines 0, you need to give all its “load” to the 2nd machines. So we get: ```[0,+8,-7,-1]```, then: ```[0,0,+1,-1]```, lastly: ```[0,0,0,0]```, done. You don’t have to worry about the details about how these machines give load to each other. __In this process, the least steps we need to eventually finish this process is determined by the peak of abs(cnt) and the max of “gain/lose” array.__ In this case, the peak of abs(cnt) is 8 and the max of gain/lose array is 7. So the result is 8.
 


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
            int curr_operation = average_dress_per_machine - dress_on_this_machine;
            operation_load = curr_operation + operation_load;
            
            // If curr_operation is positive, that means we need add dress here,
            // and we can add maximum two dresses at a time (get one from each neighbor).
            // If curr_operation is negative, that means we need give away dress,
            // but we can only give away one dresses at a time.
            reval = std::max(reval, -curr_operation);
            reval = std::max(reval, std::abs(operation_load));
        }
        
        return reval;
    }
};
```

### Solution if we think from dress need perspective

In my opinion, the lower bound of moves is determined by two factor:

* The total gain/lose between each two machines. For example in your sample data the total gain/lose between machine 1 and 2 are (-4)+(-4)=-8 and 7+1=8. This means in order to make a balance, there should be at least 8 items move from right to left between machine 1 and 2. In your algorithm this is done by Math.abs(cnt)
* The max of each individual gain/lose if positive. __The problem says “pass one dress of each washing machine to one of” which means if the gain/lose is negative, there could be at most two items moved in because there are only at most two neighbors. But if gain/lose is positive, only one can be moved out so this sets the lower bound.__

Some other example:

* machines: ```[0,3,0]```; gain/lose array: ```[-1,2,-1]```; ```max = 2, cnt = 0, -1, 1, 0```, its abs peak is 1. So result is 2.  
* machines: ```[1,0,5]```; gain/lose array: ```[-1,-2,3]```; ```max = 3, cnt = 0, -1, -3, 0```, its abs peak is 3. So result is 3. 

```cpp
class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        if (machines.empty()) return 0;
       
        long total_dresses = std::accumulate(machines.begin(), machines.end(), 0);
            
        const std::size_t num_of_machine = machines.size();
        if (total_dresses % num_of_machine != 0) return -1;
        int average_dress_per_machine = total_dresses / num_of_machine;
        
        int dress_load(0), reval(0);
        
        for (int dress_on_this_machine : machines) {
            int dress_need = dress_on_this_machine - average_dress_per_machine;
            dress_load = dress_need + dress_load;
            
            // If dress_need is negative, that means we need add dress here,
            // and we can add maximum two dresses at a time (get one from each neighbor).
            // If dress_need is positive, that means we need give away dress,
            // but we can only give away one dresses at a time.
            reval = std::max(reval, dress_need);
            reval = std::max(reval, std::abs(dress_load));
        }
        
        return reval;
    }
};
```









