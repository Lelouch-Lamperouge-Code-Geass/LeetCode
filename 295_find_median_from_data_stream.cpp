class MedianFinder {
 public:
  // Adds a number into the data structure.
  void addNum(int num) {
    if (max_heap.size() > min_heap.size()) {  // add one item on min_heap
      max_heap.push(num);
      min_heap.push(max_heap.top());
      max_heap.pop();
    } else {  // add one item on max_heap
      min_heap.push(num);
      max_heap.push(min_heap.top());
      min_heap.pop();
    }
  }

  // Returns the median of current data stream
  double findMedian() {
    return max_heap.size() != min_heap.size()
               ? max_heap.top()
               : max_heap.top() + (min_heap.top() - max_heap.top()) / 2.0;
  }

 private:
  std::priority_queue<int, vector<int>, std::greater<int> > min_heap;
  std::priority_queue<int, vector<int>, std::less<int> > max_heap;
};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();
int main() {
  string str("1,8,3,5,4,2,6,7,9");
  std::istringstream iss(str);
  MedianFinder mf;

  while (std::getline(iss, str, ',')) {
    mf.addNum(std::stoi(str));
  }
  double val = mf.findMedian();
  return 0;
}
