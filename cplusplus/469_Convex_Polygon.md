Given a list of points that form a polygon when joined sequentially, find if this polygon is convex (Convex polygon definition).

Note:

1. There are at least 3 and at most 10,000 points.
2. Coordinates are in the range -10,000 to 10,000.
3. You may assume the polygon formed by given points is always a simple polygon (Simple polygon definition). In other words, we ensure that exactly two edges intersect at each vertex, and that edges otherwise don't intersect each other.

Example 1:

```
[[0,0],[0,1],[1,1],[1,0]]

Answer: True

Explanation:
![alt](https://leetcode.com/static/images/problemset/polygon_convex.png)
```

Example 2:

```
[[0,0],[0,10],[10,10],[10,0],[5,5]]

Answer: False

Explanation:
![alt](https://leetcode.com/static/images/problemset/polygon_not_convex.png)
```

# Solution

* http://csharphelper.com/blog/2014/07/determine-whether-a-polygon-is-convex-in-c/

```cpp
class Solution {
private:
    double getCrossProduct(int ax, int ay, int bx, int by, int cx, int cy) {
        return (ax - bx) * (cy - by) -  (cx - bx) * (ay - by);
    }
public:
    bool isConvex(vector<vector<int>>& points) {
        // For each set of three adjacent points A, B, C,
        // find the cross product AB · BC. If the sign of
        // all the cross products is the same, the angles
        // are all positive or negative (depending on the
        // order in which we visit them) so the polygon
        // is convex.
        const std::size_t n = points.size();
        bool got_negative = false;
        bool got_positive = false;
        std::size_t b(0), c(0);
        for (std::size_t a = 0; a < n; ++a) {
            b = (a + 1) % n;
            c = (a + 2) % n;
            double cross_product = getCrossProduct(points[a][0], points[a][1],
                                                  points[b][0], points[b][1],
                                                  points[c][0], points[c][1]);
            if (cross_product < 0) {
                got_negative = true;
            } else if (cross_product > 0) {
                got_positive = true;
            } else {
                // Note that cross_product can be 0
            }
            
            if (got_positive && got_negative) return false;
        }
        
        // If we got this far, the polygon is convex.
        return true;
    }
};
```
