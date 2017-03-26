class Solution {
public:
  int lastRemaining(int n) {
    int head(1), remain(n), step(1);
    bool to_left(true);

    while (remain > 1) {
      if (to_left || remain % 2 == 1) {
        head += step;
      }

      remain /= 2;
      to_left = !to_left;
      step *= 2;
    }

    return head;
  }
};
