Given the running logs of n functions that are executed in a nonpreemptive single threaded CPU, find the exclusive time of these functions.

Each function has a unique id, start from 0 to n-1. A function may be called recursively or by another function.

A log is a string has this format : function_id:start_or_end:timestamp. For example, "0:start:0" means function 0 starts from the very beginning of time 0. "0:end:0" means function 0 ends to the very end of time 0.

Exclusive time of a function is defined as the time spent within this function, the time spent by calling other functions should not be considered as this function's exclusive time. You should return the exclusive time of each function sorted by their function id.

##### Example 1:

```
Input:
n = 2
logs = 
["0:start:0",
 "1:start:2",
 "1:end:5",
 "0:end:6"]
Output:[3, 4]
Explanation:
Function 0 starts at time 0, then it executes 2 units of time and reaches the end of time 1. 
Now function 0 calls function 1, function 1 starts at time 2, executes 4 units of time and end at time 5.
Function 0 is running again at time 6, and also end at the time 6, thus executes 1 unit of time. 
So function 0 totally execute 2 + 1 = 3 units of time, and function 1 totally execute 4 units of time.
```


#### Note:

1. Input logs will be sorted by timestamp, NOT log id.
2. Your output should be sorted by function id, which means the 0th element of your output corresponds to the exclusive time of function 0.
3. Two functions won't start or end at the same time.
4. Functions could be called recursively, and will always end.
5. 1 <= n <= 100

# Solution


The idea is simple everytime we see a start, we just push it to the stack. Now when we reach an end, we are guaranteed that the top of the stack is a start with the same id as the current item because all completed start/ends in between this start and end has been removed already. We just add current item timestamp - stack top timestamp + 1 to times[i].

So for example
[..., {0:start:3}] and item = {0:end:6} we add 6 - 3 + 1

However, what if there are function calls in between the start and end of the function of id 0? We can account for this by subtracting the length of the function calls in between the function id 0 whenever we complete an inner function marked by an end.

[..., {0:start:3}, {2:start:4}] and item = {2:end:5} so we increment times[2] by curr_length = 5 - 4 + 1 = 2 and then we subtract times[0] by curr_length as it takes up that amount of time out of the total time

So whenever we see an end, we have to make sure to subtract our curr_length to whatever function is enclosing it if it exists.


##### Pitfall

```
["0:start:0","0:start:2","0:end:5","0:start:6","0:end:6","0:end:7"]
```

is also a valid input, because function can call itself recursively.

```cpp
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> reval(n, 0);
        stack<int> task_ids;
        int begin_timestamp(0);
        for (const std::string &log : logs) {
            std::size_t first_colon = log.find_first_of(':');
            int task_id = std::stoi(log.substr(0, first_colon));
            
            std::size_t second_colon = log.find_first_of(':', first_colon + 1);
            const std::string status = log.substr(first_colon + 1, second_colon - first_colon - 1);
            
            int timestamp = std::stoi(log.substr(second_colon + 1));
            
            if (status == "start") {
                if (!task_ids.empty()) {
                    reval[task_ids.top()] += timestamp - begin_timestamp;
                }
                
                // new interval begins, doesn't belong to current interval.
                begin_timestamp = timestamp;
                task_ids.push(task_id);
            } else { // END
                reval[task_ids.top()] += timestamp - begin_timestamp + 1;
                task_ids.pop();
                begin_timestamp = timestamp + 1;
            }
        }
        
        return reval;
    }
};
```
