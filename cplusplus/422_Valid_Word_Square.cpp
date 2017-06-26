bool validWordSquare(vector<string>& words) {
  for(std::size_t i = 0, words_size(words.size()); i < words_size; ++i) {
    for(std::size_t j = 0, cur_size(words[i].size()); j < cur_size; ++j) {
      if(j >= words.size() || words[j].size() <= i || words[j][i] != words[i][j])
        return false;
    }
  }
  return true;
}
