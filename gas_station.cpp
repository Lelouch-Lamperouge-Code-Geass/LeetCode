//(1) Lets assume Gas[i,j] means the sum of gas from index i to index j. Same as Cost[i,j].
// (2) If Gas[0,n] >= Cost[0,n], then
//    Gas[0,k] + Gas[K+1,n] >= Cost[0,k] + Cost[K+1,n], whichs means that we can divide the array into two parts,[0,k] and [k+1,n]. And Gas[0,k]<=Cost[0,k].
//(3) Originally, the k=-1(means the right array is [0,n]).
//Iterate the array, once we meet i whose Gas[k+1,i]<Cost[k+1,i], then set k=i.
// There starting index will never be within [0,k] since its total gas < total cost.
//(4) For index within [k+1,n], since Gas[k,index] alwasy >= Cost[k,index], otherwise, k will be updated with index.

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
