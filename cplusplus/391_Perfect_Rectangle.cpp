// Solution one
class Solution {
public:
  bool isRectangleCover(vector<vector<int>>& rectangles) {
    if (rectangles.empty()) return false;

    const std::size_t row_size(rectangles.size()), col_size(rectangles[0].size());
    int x1(INT_MAX), x2(0), y1(INT_MAX), y2(0);
    std::size_t area(0);
    std::unordered_set<std::string> points_hash;
    for (vector<int> & rectangle : rectangles) {
      x1 = std::min(x1, rectangle[0]);
      y1 = std::min(y1, rectangle[1]);
      x2 = std::max(x2, rectangle[2]);
      y2 = std::max(y2, rectangle[3]);

      area += (rectangle[2] - rectangle[0]) * (rectangle[3] - rectangle[1]);

      const std::string bottom_left_point( PointHash(rectangle[0], rectangle[1]) );
      const std::string top_left_point( PointHash(rectangle[0], rectangle[3]) );
      const std::string bottom_right_point( PointHash(rectangle[2], rectangle[1]) );
      const std::string top_right_point( PointHash(rectangle[2], rectangle[3]) );

      check_point_hash(points_hash, bottom_left_point);
      check_point_hash(points_hash, top_left_point);
      check_point_hash(points_hash, bottom_right_point);
      check_point_hash(points_hash, top_right_point);
    }
    if (points_hash.size() != 4
        || points_hash.count( PointHash(x1, y1) ) == 0
        || points_hash.count( PointHash(x1, y2) ) == 0
        || points_hash.count( PointHash(x2, y1) ) == 0
        || points_hash.count( PointHash(x2, y2) ) == 0)
      return false;

    return area == (x2 - x1) * (y2 - y1);
  }
private:
  std::string PointHash(int x_axis, int y_axis) {
    return std::to_string(x_axis) + "," + std::to_string(y_axis);
  }

  void check_point_hash(std::unordered_set<std::string> & points_hash, const std::string & hash) {
    if (points_hash.count(hash) != 0) points_hash.erase(hash);
    else points_hash.insert(hash);
  }
};
