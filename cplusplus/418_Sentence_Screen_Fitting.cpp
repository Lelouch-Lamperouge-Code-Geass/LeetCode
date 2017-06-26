// https://discuss.leetcode.com/topic/62455/21ms-18-lines-java-solution/4
// if (s.charAt(start % l) == ' ') is the situation that we don't need an extra space for current row.
// The current row could be successfully fitted. So that we need to increase our counter by using start++.
// The else is the situation, which the next word can't fit to current row.
// So that we need to remove extra characters from next word.
int wordsTyping(vector<string>& sentence, int rows, int cols) {
  string concatenated_str = accumulate(sentence.begin(), sentence.end(), string(""));
  concatenated_str.push_back(' ');// Append an extra empty space
  std::size_t start(0), length(concatenated_str.size());
  for (int row = 0; row < rows; ++row) {
    start += row;
    if (s[start % length] == ' ') {
      ++ start; // Great, keep going
    } else {
      
      while(start >= 1 && concatenated_str[(start-1) % length] != ' ') {
        -- start;
      }
    }
  }

  return start / length;
}
