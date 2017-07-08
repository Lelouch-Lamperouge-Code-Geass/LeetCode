class Solution {
public:
  vector<string> readBinaryWatch(int num) {
    std::vector<std::string> reval;

    for (int hour = 0; hour < 12; ++ hour) {
      for (int minute = 0; minute < 60; ++ minute) {
        int val = (hour << 6) | minute;
        std::bitset<10> bit_counter(val);
        if (bit_counter.count() == num) {
          reval.push_back(std::to_string(hour)
                          + (minute < 10 ? ":0":":") + std::to_string(minute));
        }
      }
    }

    return reval;
  }
};
