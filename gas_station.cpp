//(1) Lets assume Gas[i,j] means the sum of gas from index i to index j. Same as Cost[i,j].
// (2) If Gas[0,n] >= Cost[0,n], then
//    Gas[0,k] + Gas[K+1,n] >= Cost[0,k] + Cost[K+1,n], whichs means that we can divide the array into two parts,[0,k] and [k+1,n]. And Gas[0,k]<=Cost[0,k].
//(3) Originally, the k=-1(means the right array is [0,n]).
//Iterate the array, once we meet i whose Gas[k+1,i]<Cost[k+1,i], then set k=i.
// There starting index will never be within [0,k] since its total gas < total cost.
//(4) For index within [k+1,n], since Gas[k,index] alwasy >= Cost[k,index], otherwise, k will be updated with index.

int minimumTotal(vector<vector<int>>& triangle) {
  if (triangle.empty()) return 0;
  vector<int> vec = triangle.back();
  const int n (triangle.size());
  for (int i=n-2;i>=0;++i) {
    for (int j=0;j<triangle[i].size();++j) {
      vec[j] = std::min(vec[j],vec[j+1]) + triangle[j];
    }
  }
  return vec[0];
}
