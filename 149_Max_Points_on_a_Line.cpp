/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
  int maxPoints(vector<Point>& points) {
    const std::size_t points_num(points.size());
    int reval(0);
    for (std::size_t i=0;i<points_num;++i) {
      unordered_map<int,unordered_map<int,int>> counter;//<key,<value,count>>
      int overlap(0),nonoverlap(0);
      for (std::size_t j=i+1;j<points_num;++j) {
        int x_diff(points[j].x-points[i].x), y_diff(points[j].y-points[i].y);
        if (x_diff==0 && y_diff==0) {
          ++ overlap;
        } else {
          int gcd = GCD(x_diff,y_diff);
          if (gcd!=0) x_diff/=gcd,y_diff/=gcd;
          ++ counter[x_diff][y_diff];
          nonoverlap = std::max(nonoverlap,counter[x_diff][y_diff]);
        }
      }
      reval = std::max(reval,overlap+nonoverlap+1);
    }
    return reval;
  }
private:
  int GCD(int a, int b){
    if (b==0) return a;
    return GCD(b,a%b);
  }
};
