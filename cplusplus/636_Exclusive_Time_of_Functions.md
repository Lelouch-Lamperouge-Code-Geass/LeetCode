Given the running logs of n functions that are executed in a nonpreemptive single threaded CPU, find the exclusive time of these functions.

Each function has a unique id, start from 0 to n-1. A function may be called recursively or by another function.

A log is a string has this format : function_id:start_or_end:timestamp. For example, ```"0:start:0"``` means function 0 starts from the very beginning of time 0. ```"0:end:0"``` means function 0 ends to the very end of time 0.

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
Now function 0 calls function 1, function 1 starts at time 2, 
executes 4 units of time and end at time 5.
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
[..., {0:start:3}] and item = {0 : end :6} we add 6 - 3 + 1

However, what if there are function calls in between the start and end of the function of id 0? We can account for this by subtracting the length of the function calls in between the function id 0 whenever we complete an inner function marked by an end.

[..., {0:start:3}, {2:start:4}] and item = {2 : end : 5} so we increment times[2] by curr_length = 5 - 4 + 1 = 2 and then we subtract times[0] by curr_length as it takes up that amount of time out of the total time

So whenever we see an end, we have to make sure to subtract our curr_length to whatever function is enclosing it if it exists.


##### Pitfall

```
["0:start:0","0:start:2","0:end:5","0:start:6","0:end:6","0:end:7"]
```

is also a valid input, because function can call itself recursively.


```cpp
class Solution {
private:
    vector<string> splitBy(const string &str, char delimiter) {
        vector<string> reval;
        size_t begin(0), end(0); 
        
        while (end != std::string::npos) {
            end = str.find_first_of(delimiter, begin);
            reval.emplace_back(str.substr(begin, end - begin));
            
            begin = end + 1;
        }
        
        return reval;
    }
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        // Stores the running time of each function
        vector<int> running_time_of_func(n, 0);
        
        // Whenever a new function begin to run, push its id to stack
        stack<int> func_ids;
        
        // Beginning timestamp of current time-slice(quantum).
        int begin_timestamp_of_curr_quantum(0);
        
        for (const string &log_line : logs) {
            const vector<string> &strs = splitBy(log_line, ':');

            const int func_id = std::stoi(strs[0]);
            const string &func_type = strs[1];
            const int timestamp = std::stoi(strs[2]);
            
            if (func_type == "start") {
                if (!func_ids.empty()) {
                    running_time_of_func[func_ids.top()] += timestamp - begin_timestamp_of_curr_quantum;
                }
                func_ids.push(func_id);
                begin_timestamp_of_curr_quantum = timestamp;
            } else { // func_type == "end"
                running_time_of_func[func_ids.top()] += timestamp + 1 - begin_timestamp_of_curr_quantum;
                func_ids.pop();
                
                 // Note here next quantum begins after current timestamp
                begin_timestamp_of_curr_quantum = timestamp + 1;
            }
            
            
        }
        
        return running_time_of_func;
    }
};
```

A different style.

```cpp
class Solution {
private:
    vector<string> parseLogEntry(const string &str) {
        vector<string> reval;
        istringstream iss(str);
        string temp("");
        
        while (std::getline(iss, temp, ':')) {
            reval.emplace_back(temp);
        }
        
        return reval;
    }
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> reval(n, 0);
        
        stack<int> func_ids;
        int quantum_start(0);
        for (const string &log_entry : logs) {
            const vector<string> &entry_items = parseLogEntry(log_entry);
            const int func_id = std::stoi(entry_items[0]);
            const string &status = entry_items[1];
            const int timestamp = std::stoi(entry_items[2]);
            if (status == "end") {
                reval[func_ids.top()] += timestamp + 1 - quantum_start;
                func_ids.pop();
                quantum_start = timestamp + 1;
            } else { // "start"
                if (!func_ids.empty()) {
                    reval[func_ids.top()] += timestamp - quantum_start;
                    quantum_start = timestamp;
                }
                func_ids.push(func_id);
            }
        }
        
        return reval;
    }
};
```
