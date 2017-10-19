Given n points on a 2D plane, find if there is such a line parallel to y-axis that reflect the given points.

Example 1:

```
Given points = [[1,1],[-1,1]], return true.
```

Example 2:

```
Given points = [[1,1],[-1,-1]], return false.
```  

Follow up:  
Could you do better than O(n2)?

# Solution


```cpp
class Solution {
public:
    bool isReflected(std::vector<std::pair<int, int>>& points) {
      int min = INT_MAX, max = INT_MIN;
      std::unordered_set<std::string> point_set;
      for (const std::pair<int,int> & point : points) {
        min = std::min(min, point.first);
        max = std::max(max, point.first);
        const std::string point_hash(std::to_string(point.first) 
          + "#" + std::to_string(point.second));
        point_set.insert(point_hash);
      }

      int sum = min + max;
      for (const std::pair<int,int> & point : points) {
        std::string mirror_point_hash(std::to_string(sum - point.first) 
          + "#" + std::to_string(point.second));
        if (point_set.count(mirror_point_hash) == 0) {
          return false;
        }
      }

      return true;
    }
};
```

### Below is my first solution

This solution is just ok.
  
Because I tried to find the median of max x and min x, then I have to use double type, definitely can't use integer here.
  
  

```cpp
class Solution {
public:
    bool isReflected(vector<pair<int, int>>& points) {
        if (points.empty()) return true;
        
        int min_x(points[0].first), max_x(points[0].first);
        unordered_map<double, unordered_set<double>> mapper;
        for (const pair<int,int> &point : points) {
            min_x = std::min(min_x, point.first);
            max_x = std::max(max_x, point.first);
            mapper[point.first].insert(point.second);
        }
        
        double mid_x = min_x + (max_x - min_x) / 2.0;
        
        for (const pair<int,int> &point : points) {
            double diff = point.first - mid_x;
            if (mapper.count(mid_x - diff) == 0
                || mapper[mid_x - diff].count(point.second) == 0) {
                return false;
            }
        }
        
        return true;
    }
};
```
