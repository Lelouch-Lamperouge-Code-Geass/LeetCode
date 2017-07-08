class Solution {
public:
  vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
    std::sort(people.begin(), people.end(),
              [](const std::pair<int,int> & left, const std::pair<int,int> & right){
                            return left.first > right.first
                              || (left.first == right.first && left.second < right.second);
              });

    std::vector< std::pair<int,int> > reval;
    for (const std::pair<int,int> & person : people) {
      reval.insert(reval.begin() + person.second, person);
    }

    return reval;
  }
};
