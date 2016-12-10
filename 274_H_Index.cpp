/* Solution 1*/
class Solution {
public:
  int hIndex(vector<int>& citations) {
    // Get total papers amount
    const int paper_amount(citations.size()+1);

    // For this vector, index represent citations,
    // value represents papers count.
    vector<int> citation_count(paper_amount,0);

    for (int citation : citations) {
      if (citation>=paper_amount) {
        ++ citation_count[paper_amount-1];
      } else {
        ++ citation_count[citation];
      }
    }

    int count_so_far(0);
    for (int i=paper_amount-1; i>=0; --i) {
      count_so_far += citation_count[i];
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
