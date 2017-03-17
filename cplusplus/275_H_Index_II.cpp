class Solution {
public:
  int hIndex(vector<int>& citations) {
    int size(citations.size()),low(0), high(size-1);
    while (low<=high) {
      int mid = low + (high-low) / 2;
      int paper_count = size-mid;
      if (paper_count > citations[mid]) {
        low = mid + 1;
      } else if (paper_count < citations[mid]) {
        high = mid - 1;
      } else {
        return paper_count;
      }
    }
    return size-low;
  }
};
