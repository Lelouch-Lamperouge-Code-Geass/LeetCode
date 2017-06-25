class Solution {
public:
  int numberOfBoomerangs(vector<pair<int, int>>& points) {
    const std::size_t points_size(points.size());
    int reval(0);
    std::unordered_map <std::size_t, std::size_t> distance_mapper;
    for (std::size_t i = 0; i < points_size; ++i) {
      for (std::size_t j = 0; j < points_size; ++j) {
        if (j == i) continue;
        // No need to get square root here
        std::size_t distance = get_distance(points[i], points[j]);
        ++ distance_mapper[distance];
      }

      for (const auto & pair : distance_mapper) {
        reval += pair.second * (pair.second - 1);
      }

      distance_mapper.clear();
    }

    return reval;
  }
private:
  std::size_t get_distance(const pair<int,int> & x, const pair<int,int> & y) {
    return std::pow((y.first - x.first), 2)
      + std::pow((y.second - x.second), 2)  ;
  }
};
