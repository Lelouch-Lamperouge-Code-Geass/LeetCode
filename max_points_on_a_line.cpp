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
    const int n(points.size());
    int reval(0);
    for (int i=0;i<n;++i) {
      unordered_map< int,unordered_map<int,int> > counter;
      int overlap(0),non_overlap_max(0),vertical(0);
      for (int j=i+1;j<n;++j) {
        int diff_x = points[j].x-points[i].x;
        int diff_y = points[j].y-points[i].y;
        int gcd_val = gcd(diff_x,diff_y);
        if (diff_x==0 && diff_y==0) {
          ++ overlap;
        } else if (diff_x==0 ) {
          ++ vertical;
        } else {
          int cur_max = ++ counter[diff_x/gcd_val][diff_y/gcd_val];
          non_overlap_max = std::max(non_overlap_max,cur_max);
        }
      }
      reval = std::max(reval,non_overlap_max + overlap + 1);
      reval = std::max(reval,vertical + overlap + 1);
    }
    return reval;
  }

  int gcd (int a, int b) {
    if (b==0) return a;
    return gcd(b,a%b);
  }
};
