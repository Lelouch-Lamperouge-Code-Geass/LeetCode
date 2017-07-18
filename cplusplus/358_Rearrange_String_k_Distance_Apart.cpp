#include <cassert>
#include <string>
#include <climits>
#include <iostream>
#include <queue>
#include <unordered_map>

namespace SolutionOne {
  // Find the character with the largest remaining count.
  // Use valid array to keep track of the most left position that character can appear.
  // Since both array are fixed-size(256), the time-complexity of this function is constant.
  int findValidMax(int count[], int valid[], std::size_t index) {
    int max = INT_MIN;
    int candidate_char = -1;
    for (int i = 0; i < 256; ++i) {
      if (count[i] > 0 && count[i] > max && index >= valid[i]) {
        max = count[i];
        candidate_char = i;
      }
    }
    return candidate_char;
  }
  // Time complexity is O(n)
  std::string rearrangeString(std::string str, int k) {
    std::size_t str_size(str.size());
    int count[256] = {0};
    int valid[256] = {0};
    for (char c : str) {
      ++ count[c];
    }

    std::string reval("");
    for (std::size_t index = 0; index < str_size; ++index) {
      int candidate_char = findValidMax(count, valid, index);
      if (candidate_char == -1) return "";
      --count[candidate_char];
      valid[candidate_char] = index +  k;
      reval.push_back((char)candidate_char);
    }
    return reval;
  }
}

namespace SolutionTwo {
  std::string rearrangeString(std::string str, int k) {
    if(k == 0) return str;
    int length = (int)str.size();

    std::string res;
    std::unordered_map<char, int> dict;
    std::priority_queue<std::pair<int, char>> pq;

    for(char ch : str) dict[ch]++;
    for(auto it = dict.begin(); it != dict.end(); it++){
      pq.push(std::make_pair(it->second, it->first));
    }

    while(!pq.empty()){
      std::vector<std::pair<int, char>> cache; //store used char during one while loop
      int count = std::min(k, length); //count: how many steps in a while loop
      for(int i = 0; i < count; i++){
        if(pq.empty()) return "";
        auto tmp = pq.top();
        pq.pop();
        res.push_back(tmp.second);
        if(--tmp.first > 0) cache.push_back(tmp);
        length--;
      }
      for(auto p : cache) pq.push(p);
    }
    return res;
  }
}
void UnitTest() {
  using namespace SolutionTwo;
  assert(rearrangeString("aabbcc", 3) == "abcabc");
  assert(rearrangeString( "aaabc", 3) == "");
}


int main() {
  //UnitTest();
  using namespace SolutionTwo;
  std::cout << rearrangeString( "aabbc", 3) << std::endl;
  std::cout << rearrangeString( "geeksforgeeks", 3) << std::endl;
  return 0;
}
