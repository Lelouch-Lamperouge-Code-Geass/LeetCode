class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int size1(nums1.size()), size2(nums2.size());
        
        if (size2<size1)
            return findMedianSortedArrays(nums2,nums1);
        
        int n = size1 + size2, half = (n+1)/2;
        
        // low,high represent the smallest and largest length we can use in nums1
        int low(0),high(size1);
        // len1,len2 represent the length we choose from nums1,nums2 to compose left half
        int len1(0),len2(0);
        
        // the important 4 elements:
        // nums1[len1-1],nums1[len1],nums2[len2-1],nums2[len2]
        while (low <= high) {
            len1 = low + (high - low) / 2;
            len2 = half - len1;
            if (len1<size1 && nums1[len1] < nums2[len2-1]) {
              low = len1 + 1;
            } else if (len1-1>=0 && nums1[len1-1] > nums2[len2]) {
              high = len1 -1;
            } else {
              break;
            }
        }
        
        //get max of left half
        int max_of_left(-1);
        if (len1==0) {
            max_of_left = nums2[len2-1];
        } else if (len2==0) {
            max_of_left = nums1[len1-1];
        } else {
            max_of_left = std::max(nums1[len1-1],nums2[len2-1]);
        }
        
        if(n & 1 == 1) return max_of_left; // is total number odd?
        
        //get min of right half
        int min_of_right(-1);
        if (len1==size1) {
            min_of_right = nums2[len2];
        } else if (len2==size2) {
            min_of_right = nums1[len1];
        } else {
            min_of_right = std::min(nums1[len1],nums2[len2]);
        }
        
        return (max_of_left+min_of_right) / 2.0;
    }
};
