class Solution {
public:
  string frequencySort(string s) {
    std::unordered_map<char, std::size_t> freq;

    for (char c : s) {
      ++ freq[c];
    }

    std::vector<std::string> buckets(s.size() + 1, "");
    for (const std::pair<char, size_t> & item : freq) {
      buckets[item.second].append(item.second, item.first);
    }

    std::string reval("");
    for (std::size_t s_size = s.size(), i = s_size; i <= s_size; --i) {
      if (!buckets[i].empty()) {
        reval.append(buckets[i]);
      }
    }

    return reval;
  }
};
