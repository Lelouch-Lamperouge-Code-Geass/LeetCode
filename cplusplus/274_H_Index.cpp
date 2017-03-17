/* Solution 1*/
class Solution {
public:
  int hIndex(vector<int>& citations) {
    const int paper_amount(citations.size()+1);

    // 统计各个引用次数对应多少篇文章
    vector<int> stats(paper_amount,0);

    for (int citation : citations) {
      ++ stats[ citation<paper_amount? citation : paper_amount-1];
    }

    int count_so_far(0);
    for (int i=paper_amount-1; i>=0; --i) {
      count_so_far += stats[i];
      if (count_so_far>=i) return i;
    }
    return 0;
  }
};

/* Solution 2*/
class Solution {
public:
  int hIndex(vector<int>& citations) {
    std::sort( citations.begin() , citations.end() , std::greater<int>());
    int index(0);
    while(index < citations.size() && citations[index] >= index+1)
      ++ index;
    return index;
  }
};
