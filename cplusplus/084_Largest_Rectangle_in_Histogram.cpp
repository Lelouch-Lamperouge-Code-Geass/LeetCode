/*
The idea is simple: for a given range of bars, the maximum area can either from left or right half of the bars, 
or from the area containing the middle two bars. For the last condition, expanding from the middle two bars to 
find a maximum area is O(n), which makes a typical Divide and Conquer solution with T(n) = 2T(n/2) + O(n). 
Thus the overall complexity is O(nlgn) for time and O(1) for space (or O(lgn) considering stack usage).
*/
class Solution {
public:
  int largestRectangleArea(vector<int>& heights) {
    if (heights.empty()) {
      return 0;
    }
    return maxArea(heights, 0, heights.size()-1);
  }
private:
  int maxArea(const vector<int> & heights, int start, int end) {
    // if the range only contains one bar, return its height as area
    if (start == end) {
      return heights[start];
    }
    // otherwise, divide & conquer, the max area must be among the following 3 values
    int mid = start + (end-start)/2;
    // 1 - max area from left half
    int area = maxArea(heights, start, mid);
    // 2 - max area from right half
    area = max(area, maxArea(heights, mid+1, end));
    // 3 - max area across the middle
    area = max(area, maxCombineArea(heights, start, mid, end));
    return area;
  }

  int maxCombineArea(const vector<int> & heights, int start, int mid, int end) {
    // Expand from the middle to find the max area containing heights[m] and heights[m+1]
    int i = mid, j = mid+1;
    int area = 0, h = min(heights[i], heights[j]);
    while(i >= start && j <= end) {
      h = min(h, min(heights[i], heights[j]));
      area = max(area, (j-i+1) * h);
      if (i == start) {
        ++j;
      }
      else if (j == end) {
        --i;
      }
      else {
        // if both sides have not reached the boundary,
        // compare the outer bars and expand towards the bigger side
        if (heights[i-1] > heights[j+1]) {
          --i;
        }
        else {
          ++j;
        }
      }
    }
    return area;
  }
};

/*
The idea is simple, use a stack to save the index of each vector entry in a non-descending order; 
once the current entry is smaller than the one with the index s.top(), then that means the rectangle with the height height[s.top()] 
ends at the current position, so calculate its area and update the maximum.
The only trick I use to avoid checking whether the stack is empty (due to pop) and also avoiding emptying the stack 
at the end (i.e. after going through the vector, s is not empty and we have to consider those in the stack) is to put a 
dummy "0" at the beginning of vector "height" and the end of "height": the first one makes sure the stack will never be 
empty (since all the height entries are >=0) and the last one will flush all the remaining non-zero entries of the stack 
at the end of "for" iteration. This trick helps us keep the code concise.
*/
class Solution {
public:
  int largestRectangleArea(vector<int>& heights) {
    heights.push_back(0);
    const std::size_t heights_size(heights.size());
    int max_area(0);
    vector<std::size_t> non_descend_heights;
    for (std::size_t i=0;i<heights_size;++i) {
      while (!non_descend_heights.empty() && heights[non_descend_heights.back()]>heights[i]) {
        int height = heights[non_descend_heights.back()];
        non_descend_heights.pop_back();
        int width = non_descend_heights.empty()? i : i-non_descend_heights.back()-1;
        max_area = std::max(max_area,height*width);
      }
      non_descend_heights.push_back(i);
    }
    heights.pop_back(); // revert back
    return max_area;
  }
};


