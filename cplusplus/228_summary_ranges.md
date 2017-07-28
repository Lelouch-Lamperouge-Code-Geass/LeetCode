Given a sorted integer array without duplicates, return the summary of its ranges.

For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].

# Solution
 
```cpp

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> reval;
        
        if ( !nums.empty() ) {
            std::size_t start(0);
            for (std::size_t i = 1, n = nums.size(); i < n; ++ i) {
                if (nums[i] != nums[i - 1] + 1) {
                    reval.push_back(generateRangeString(nums[start], nums[i - 1]));
                    start = i;
                }
            }
            
            // Last item
            reval.push_back(generateRangeString(nums[start], nums[nums.size() - 1]));
        }
        
        return reval;   
    }
    
private:
    std::string generateRangeString(int start, int end) {
        return start == end ? std::to_string(start) : std::to_string(start) + "->" + std::to_string(end);
    }
};
```
