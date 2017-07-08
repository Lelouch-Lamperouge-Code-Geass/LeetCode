class Solution {
public:
  bool validUtf8(vector<int>& data) {
    int coming_count(0);

    for (int num : data) {
      if (coming_count == 0) {
        if ( (num >> 3) == 0x1E) { // 4 bytes
          coming_count = 3;
        } else if ( (num >> 4) == 0x0E ) { // 3 bytes
          coming_count = 2;
        } else if ( (num >> 5) == 0x06 ) { // 2 bytes
          coming_count = 1;
        } else {
          if ( (num >> 7) ) return false;
        }
      } else {
        if ( (num >> 6) != 0x2) return false;
        -- coming_count;
      }
    }

    return coming_count == 0;
  }
};
