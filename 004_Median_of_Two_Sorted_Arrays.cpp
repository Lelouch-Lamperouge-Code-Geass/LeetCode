class Solution {
public:
    
double findMedianSortedArrays( std::vector<int> & left,  std::vector<int> & right) {
  const std::size_t left_size(left.size()), right_size(right.size()), total_size(left_size + right_size);

  if (left_size > right_size) return findMedianSortedArrays(right, left);

  // if total_size is 9, make left_sub_size to be 5, and right_sub_size to be 4
  std::size_t left_sub_size( (total_size + 1) / 2);

  // low, high represents the number of elements we can take from left vector
  std::size_t low(0), high(left_size);

  std::size_t len_one(0), len_two(0);
  
  while (low <= high) {
    len_one = low + (high - low ) / 2;
    len_two = left_sub_size - len_one;

    if (len_one < left_size && left[len_one] < right[len_two-1]) {
      low = len_one + 1;
    } else if(len_one >= 1 && left[len_one-1] > right[len_two]) {
      high = len_one - 1;
    } else {
      break;
    }
  }

  int max_of_left(0);
  if (len_one == 0) {
    max_of_left = right[len_two-1];
  } else if (len_two == 0) {
    max_of_left = left[len_one-1];
  } else {
    max_of_left = std::max(left[len_one-1], right[len_two-1]);
  }

  if (total_size % 2 == 1) {
    return max_of_left;
  }

  int min_of_right(0);
  if (len_one == left_size) {
    min_of_right = right[len_two];
  } else if (len_two == right_size) {
    min_of_right = left[len_one];
  } else {
    min_of_right = std::min(left[len_one], right[len_two]);
  }


  return (double(max_of_left) + double(min_of_right) )/ 2.0 ;
}


};
