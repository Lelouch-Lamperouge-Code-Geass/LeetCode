
bool isReflected(std::vector<std::pair<int, int>>& points) {
  int min = INT_MAX, max = INT_MIN;
  std::unordered_set<std::string> point_set;
  for (const std::pair<int,int> & point, points) {
    min = std::min(min, point.first);
    max = std::max(max, point.first);
    const std::string point_hash(std::to_string(point.first) + "#" + std::to_string(point.second));
    point_set.insert(point_hash);
  }

  int sum = min + max;
  for (const std::pair<int,int> & point, points) {
    std::string mirror_point_hash(std::to_string(sum - point.first) + "#" + std::to_string(point.second));
    if (point_set.count(mirrow_point_hash) == 0) {
      return false;
    }
  }

  return true;
}
