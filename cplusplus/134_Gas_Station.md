There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

__Note:__

The solution is guaranteed to be unique.

# Solution
  
I have thought for a long time and got two ideas:

1. If the total number of gas is bigger than the total number of cost. There must be a solution.  
2. If car starts at A and can not reach B. Any station between A and B can not reach B.(B is the first station that A can not reach.)  
  
Proof to the second point: say there is a point C between A and B -- that is A can reach C but cannot reach B. Since A cannot reach B, the gas collected between A and B is short of the cost. Starting from A, at the time when the car reaches C, it brings in gas >= 0, and the car still cannot reach B. Thus if the car just starts from C, it definitely cannot reach B.


//(1) Lets assume Gas[i,j] means the sum of gas from index i to index j. Same as Cost[i,j].
// (2) If Gas[0,n] >= Cost[0,n], then
//    Gas[0,k] + Gas[K+1,n] >= Cost[0,k] + Cost[K+1,n], whichs means that we can divide the array into two parts,[0,k] and [k+1,n]. And Gas[0,k]<=Cost[0,k].
//(3) Originally, the k=-1(means the right array is [0,n]).
//Iterate the array, once we meet i whose Gas[k+1,i]<Cost[k+1,i], then set k=i.
// There starting index will never be within [0,k] since its total gas < total cost.
//(4) For index within [k+1,n], since Gas[k,index] alwasy >= Cost[k,index], otherwise, k will be updated with index.


```cpp
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
  const int n(gas.size());
  int total_cost(0),total_gas(0),tank(0),index(0);
  for (int i=0;i<n;++i) {
    total_gas += gas[i];
    total_cost += cost[i];

    tank += gas[i];
    tank -= cost[i];

    if (tank<0) { // reset begin index
      tank = 0;
      index = i+1;
    }
  }
  return total_gas >= total_cost ? index : -1;
}
```
