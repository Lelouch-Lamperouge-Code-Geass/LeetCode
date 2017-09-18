Design a logger system that receive stream of messages along with its timestamps, each message should be printed if and only if it is not printed in the last 10 seconds.
Given a message and a timestamp (in seconds granularity), return true if the message should be printed in the given timestamp, otherwise returns false.
It is possible that several messages arrive roughly at the same time.
Example:

```
Logger logger = new Logger();

// logging string "foo" at timestamp 1
logger.shouldPrintMessage(1, "foo"); returns true; 

// logging string "bar" at timestamp 2
logger.shouldPrintMessage(2,"bar"); returns true;

// logging string "foo" at timestamp 3
logger.shouldPrintMessage(3,"foo"); returns false;

// logging string "bar" at timestamp 8
logger.shouldPrintMessage(8,"bar"); returns false;

// logging string "foo" at timestamp 10
logger.shouldPrintMessage(10,"foo"); returns false;

// logging string "foo" at timestamp 11
logger.shouldPrintMessage(11,"foo"); returns true;

```

# Solution

### Solution 1

Instead of logging print times, I store when it's ok for a message to be printed again. Should be slightly faster, because I don't always have to add or subtract (e.g., timestamp < log[message] + 10) but only do in the true case. Also, it leads to a shorter/simpler longest line of code. Finally, C++ has 0 as default, so I can just use ok[message].

```cpp
class Logger {
public:

    map<string, int> ok;

    bool shouldPrintMessage(int timestamp, string message) {
        if (timestamp < ok[message])
            return false;
        ok[message] = timestamp + 10;
        return true;
    }
};
```

### Solution 2
A typical (accepted) solution is to keep a hash map of String that maps to the recent time stamp.
But this way, it needs to keep the record of the entire messages, even when the message is rare.

Alternatively, I keep a heap to get rid of the old message and set of String to keep the recent messages only. This approach would make sense when the number of logs within 10 minutes time window is not too large and when we have lots of different messages.

```java
class Log {
    int timestamp;
    String message;
    public Log(int aTimestamp, String aMessage) {
        timestamp = aTimestamp;
        message = aMessage;
    }
}

public class Logger {
    PriorityQueue<Log> recentLogs;
    Set<String> recentMessages;   
    
    /** Initialize your data structure here. */
    public Logger() {
        recentLogs = new PriorityQueue<Log>(10, new Comparator<Log>() {
            public int compare(Log l1, Log l2) {
                return l1.timestamp - l2.timestamp;
            }
        });
        
        recentMessages = new HashSet<String>();
    }
    
    /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
        If this method returns false, the message will not be printed.
        The timestamp is in seconds granularity. */
    public boolean shouldPrintMessage(int timestamp, String message) {
        while (recentLogs.size() > 0)   {
            Log log = recentLogs.peek();
            // discard the logs older than 10 minutes
            if (timestamp - log.timestamp >= 10) {
                recentLogs.poll();
                recentMessages.remove(log.message);
            } else 
            	break;
        }
        boolean res = !recentMessages.contains(message);
        if (res) {
            recentLogs.add(new Log(timestamp, message));
            recentMessages.add(message);
        }
        return res;
    }
}
/**
 * Your Logger object will be instantiated and called as such:
 * Logger obj = new Logger();
 * boolean param_1 = obj.shouldPrintMessage(timestamp,message);
 */
```
