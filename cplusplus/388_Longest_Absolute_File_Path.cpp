class Solution {
public:
  int lengthLongestPath(string input) {
    int reval(0);
    std::vector<std::string> lines = GetLinesByDelimiter(input, '\n');
    std::vector<int> level_lens(lines.size() + 1, 0); // We add one more level = 0  as the root
    for (const std::string & line : lines) {
      const std::size_t last_tab = line.find_last_of('\t');
      // Here level is also equals to how many '\t' the line has
      int level = (last_tab == std::string::npos ? 0 : last_tab + 1);
      if (line.find('.') != std::string::npos) { // it is a file
        // dir + subdir1 + \t\tsubsubdir1
        // And if you look at the result closely,here the number of '\t'
        // are the same of the number of '\' we finally need.
        reval = std::max(reval, level_lens[level] + (int)line.size());
      } else { // it is a directory
        level_lens[level + 1] = level_lens[level] + line.size() - level;
      }
    }

    return reval;
  }
private:
  std::vector<std::string> GetLinesByDelimiter(const std::string & str,
                                               const char delimiter) {
    std::vector<std::string> reval;
    std::istringstream iss(str);
    std::string temp("");
    while (std::getline(iss, temp, delimiter)) {
      reval.push_back(temp);
    }

    return reval;
  }
};
