Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

For example,
```
Given [[0, 30],[5, 10],[15, 20]],
return 2.
```
# Solution

> A greedy algorithm is an algorithmic paradigm that follows the problem solving __heuristic__ of making the locally optimal choice at each stage with the hope of finding a __global optimum__. In many problems, a greedy strategy does not in general produce an optimal solution, but nonetheless a greedy heuristic may yield locally optimal solutions that approximate a global optimal solution in a reasonable time.

If you look at these events in a time line one after another (like stream data), then this solution is a greedy solution.

The heap stores all conflicting events, which must be resolved by independent rooms. The heap's head is the event that has earliest end/finish time. All other events collide with each other mutually in the heap.

When a new event comes (this is the reason that we need to sort by event.start), we greedily choose the event A that finished the earliest (this is the reason that we use minheap on end time). If the new event does not collide with A, then the new event can re-use A's room, or simply extend A's room to the new event's end time.

If the new event collides with A, then it must collide with all events in the heap. So a new room must be created.

The reason for correctness is the invariant: heap size is always the minimum number of rooms we need so far. If the new event collides with everyone, then a new room must be created; if the new event does not collide with someone, then it must not collide with the earliest finish one, so greedily choose that one and re-use that room. So the invariant is maintained.

__Time complexity O(NlogN)__.

```cpp
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        if (intervals.empty()) return 0;
        static auto StartEarlier = [](const Interval &left, const Interval &right){
            return left.start < right.start || left.start == right.start && left.end < right.end;
        };
        // Sort the intervals by start time
        std::sort(intervals.begin(), intervals.end(), StartEarlier);
        
        // Use a min heap to track the minimum end time of merged intervals
        std::priority_queue<int, std::vector<int>, std::greater<int>> meeting_rooms;
        
         // start with the first meeting, put it to a meeting room
        meeting_rooms.push(intervals[0].end);
        
        
        for (std::size_t i = 1, n = intervals.size(); i < n; ++i) {
            // get the meeting room that finishes earliest
            int earliest_end = meeting_rooms.top();
            if (earliest_end <= intervals[i].start) { 
                // if the current meeting starts right after 
                // there's no need for a new room, just reuse the exsiting one
                meeting_rooms.pop();
                meeting_rooms.push(intervals[i].end);
            } else { 
                // add meeting room
                meeting_rooms.push(intervals[i].end);
            }
        }
        
        return meeting_rooms.size();
    }
};
```

### What if we want to store Interval?

Unlike above solution, here we store the Interval instead just end-time.

#### Using lambda expression

I paste the code here because it shows how should we use lambda expression to define comparator when it comes to template container.

```cpp
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        std::sort(intervals.begin(), intervals.end(), [](const Interval &left, const Interval &right){
            return left.start < right.start;
        });
        
        auto end_earlier_comparison = [](const Interval &left, const Interval &right) -> bool{
            return left.end > right.end;
        };
        
        std::priority_queue<Interval, vector<Interval>,  decltype(end_earlier_comparison)> meeting_rooms(end_earlier_comparison);
        
        for (const Interval &inter : intervals) {
            if (meeting_rooms.empty() || inter.start < meeting_rooms.top().end) {
                // Add meeting room
                meeting_rooms.push(inter);
            } else {
                // If the current meeting starts right after the meeting room ending earliest,
                // there's no need for a new room, just reuse the exsiting one
                Interval new_item = meeting_rooms.top();
                meeting_rooms.pop();
                new_item.end = std::max(new_item.end, inter.end);
                meeting_rooms.push(new_item);
            }
        }
        
        return meeting_rooms.size();
    }
};
```

#### Using functor

Functors are objects that can be treated as though they are a function or function pointer. 

```cpp
class Solution {
private:
    // A functor
    struct EndEarlier {
        public:
            bool operator() (const Interval &left, const Interval &right){
                return left.end > right.end;
            }
    };
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        std::sort(intervals.begin(), intervals.end(), [](const Interval &left, const Interval &right){
            return left.start < right.start;
        });
        
        auto end_earlier_comparison = [](const Interval &left, const Interval &right) -> bool{
            return left.end > right.end;
        };
        
        std::priority_queue<Interval, vector<Interval>, EndEarlier> meeting_rooms;
        
        for (const Interval &inter : intervals) {
            if (meeting_rooms.empty() || inter.start < meeting_rooms.top().end) {
                // Add meeting room
                meeting_rooms.push(inter);
            } else {
                // If the current meeting starts right after the meeting room ending earliest,
                // there's no need for a new room, just reuse the exsiting one
                Interval new_item = meeting_rooms.top();
                meeting_rooms.pop();
                new_item.end = std::max(new_item.end, inter.end);
                meeting_rooms.push(new_item);
            }
        }
        
        return meeting_rooms.size();
    }
};
```

### Knowledge

Lambda expression help us to construct a __closure__: an __unnamed function object__ capable of capturing variables in scope. _A lambda is not a function pointer! A lambda is an instance of compiler generated class!_


Can we do something like ```Foo<decltype([]()->void { })> foo;``` ?

No you can't, because lambda expressions shall not appear in an __unevaluated context__ (such as __decltype__ and __sizeof__, amongst others). 

> The evaluation of a lambda-expression results in a prvalue temporary (12.2). This temporary is called the closure object. A lambda-expression shall not appear in an unevaluated operand (Clause 5). [ Note: A closure object behaves like a function object (20.8).—end note ]

##### Sort numbers

```
int numbers[]={20,40,50,10,30};
std::sort (numbers, numbers+5, std::greater<int>());
```

Why are there parentheses after std::greater there? Are we creating a new std::greater object here?

That's correct. The expression std::greater<int>() corresponds to creating an object of type std::greater<int>.

##### Define container

```
std::priority_queue<int, std::vector<int>, std::greater<int>> meeting_rooms;
```

The class template std::priority_queue expects that the argument will be of a __function object type__ that is a pointer to function or a class type that has a function operator.


https://stackoverflow.com/questions/44240996/difference-between-stdgreaterint-and-stdgreaterint
