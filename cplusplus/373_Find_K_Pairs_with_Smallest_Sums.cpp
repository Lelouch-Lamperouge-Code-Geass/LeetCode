class Solution {
private:
  struct Item {
    Item(int current_nums1_value,
         int current_nums2_value,
         int current_nums2_index)
      : m_current_nums1_value(current_nums1_value),
        m_current_nums2_value(current_nums2_value),
        m_current_nums2_index(current_nums2_index){

    }
    int m_current_nums1_value;
    int m_current_nums2_value;
    std::size_t m_current_nums2_index;
  };
  struct ItemCompare {
  public:
    bool operator()(const Item & left, const Item & right) {
      return  (left.m_current_nums1_value + left.m_current_nums2_value)
        > (right.m_current_nums1_value + right.m_current_nums2_value);
    }
  };
public:
  vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    vector<pair<int, int>> reval;
    if (nums1.empty() || nums2.empty() || k <= 0) return reval;
    std::priority_queue<Item, std::vector<Item>, ItemCompare> min_queue;

    const std::size_t nums1_size(nums1.size()), nums2_size(nums2.size());

    for (std::size_t i = 0; i < nums1_size; ++i) {
      min_queue.push(Item(nums1[i], nums2[0], 0));
    }

    while (k-- > 0 && !min_queue.empty()) {
      const Item cur_item(min_queue.top());
      reval.push_back(std::make_pair( cur_item.m_current_nums1_value,
                                      cur_item.m_current_nums2_value)
                      );
      min_queue.pop();

      if (cur_item.m_current_nums2_index + 1 < nums2_size) {
        min_queue.push(Item(cur_item.m_current_nums1_value,
                            nums2[cur_item.m_current_nums2_index + 1],
                            cur_item.m_current_nums2_index + 1));
      }
    }

    return reval;
  }
};
