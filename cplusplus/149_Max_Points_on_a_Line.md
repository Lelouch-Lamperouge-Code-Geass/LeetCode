Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
  
  
# Solution
  
The equation of any straight line, called a linear equation, can be written as: ```y = a * x + b```, where m is the __slope__ of the line and b is the __y-intercept__. The y-intercept of this line is the value of y at the point where the line crosses the y axis.

For two points(x1,y1), (x2,y2) on the same line,  we have ```(y2-y1) = a * (x2-x1), a = (y2-y1)/(x2-x1)```.
  
For any point A, if point B and point C have the same slope, then these three points are on the same line. 
  
Therefore, all we need to do is go through each point, and calculate the the slope of it and other points. For points that have the same slope against this target point, they are on the same line.
  
You may intuitively use double or float to record the slope value.
  
However, remember that floating number is not accurate in computer system.
  
Therefore, instead of storying ```(y2 - y1) / (x2 - x1)``` as a float or double number, we need store them ```(x2 - x1), (y2 - y1)``` as a pair in HashMap. But before we put them into HashMap, we need to divide them with their __greatest  common diviser__. 
  
__Note__:

1. Some points can overlap.
2. Greast common divisor will only return 0 when both a and b are 0.
3. Greast common divisor should be able to handle negative number as well.
  
```cpp
class Solution {
private:
    // Return greatest common divisor of a, b.
    // It will only return 0 when both a and b are 0.
    int GreatestCommonDivisor(int a, int b) {
        if (b == 0) return a;
        return GreatestCommonDivisor(b,a % b);   
    }
public:
    int maxPoints(vector<Point>& points) {
        int reval(0);
        
        std::unordered_map<int, std::unordered_map<int, int>> counter;
        for (std::size_t i = 0, n = points.size(); i < n; ++i) {
            counter.clear(); // Important to clear counter!
            // Be careful with overlap points, they make gcd to be 0.
            int overlap(1), non_overlap(0);           
            for (std::size_t j = i + 1; j < n; ++j) {
                int diff_x = points[j].x - points[i].x;
                int diff_y = points[j].y - points[i].y;              
                if (diff_x == 0 && diff_y == 0) {
                    ++ overlap;
                } else {
                    int gcd = GreatestCommonDivisor(diff_x, diff_y); // gcd won't be 0 here
                    non_overlap = std::max(non_overlap, ++ counter[diff_x / gcd][diff_y / gcd]);
                }
            }
            
            // Overlap points can be on any line, here overlap already count itself.
            // Now we have the max points count including current point.
            // Let's compare it with final result.
            reval = std::max(reval, non_overlap + overlap);
        }
        
        return reval;
    }
};
```

