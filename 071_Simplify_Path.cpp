class Solution {
public:
  string simplifyPath(string path) {
    std::vector<std::string> pathes;
    std::istringstream iss(path);
    std::string temp("");
    while (std::getline(iss,temp,'/')) {
      if (temp.empty()||temp==".") {
        continue;
      } else if (temp=="..") {
        if (!pathes.empty()) pathes.pop_back();
      } else {
        pathes.push_back(temp);
      }
    }

    std::string reval("");
    for (const std::string & str : pathes) {
      reval+="/"+str;
    }
    return reval.empty()? "/" : reval;
  }
};
