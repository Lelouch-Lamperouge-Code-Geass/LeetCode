Find the total area covered by two rectilinear rectangles in a 2D plane.

Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.

![alt](https://leetcode.com/static/images/problemset/rectangle_area.png)    
    
Assume that the total area is never beyond the maximum possible value of int.    
   
# Solution

#### To know whether the two areas are not overlapped:

We actually only need to consider four situations: B>=H or E>=C or F>=D or A>=G. For example, if B is larger than H, the area (A,B,C,D) is definitely not overlapped with area (E,F,G,H), and we even know that area (A,B,C,D) is on the upper area of the plot compared with area (E,F,G,H). You can also check if other situations work.

#### To calculate the overlapped area:

When the two areas are overlapped, we only need to know the bottom left corner and top right corner of the overlapped area: the larger one of A and E, the larger one of B and F, the smaller one of C and G, and the smaller one of D and H. For example, in the case of the given figure of the original problem, we just consider the point (E,B) and the point (C,H), and the overlapped area is (E,B,C,H) which could be calculated intuitively. So how about other kinds of overlapping? The formula given above never change! You can try imagining other kind of overlapped area, you will see that in any case we only need to know max(A,E), max(B,F), min(C,G), and min(D,H) to calculate the overlapped area.       
       
       
```cpp
class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int left = std::max(A,E),down = std::max(B,F),right = std::min(C,G), top = std::min(D,H);
        int overlap(0);
        if(right > left && top > down) {
             overlap = (right - left) * (top - down);
         }
        return (C-A)*(D-B) + (G-E)*(H-F) - overlap;
    }
};
```
