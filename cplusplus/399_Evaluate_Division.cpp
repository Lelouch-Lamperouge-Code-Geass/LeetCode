/*
  Solution one : 
 */
class Solution {
public:
  vector<double> calcEquation(vector<pair<string, string>> equations,
                              set<std::string> visited;
                              double val = SeekWithDFS(from, to, edge_weights, visited, 1.0);
                              reval.push_back(val);
                              }
    } else {
  reval.push_back(-1.0);
 }
}

return reval;
}

private:
double SeekWithDFS(const std::string & from,
                   const std::string & to,
                   std::unordered_map<std::string,
                   std::unordered_map<std::string, double> > & edge_weights,
                   std::unordered_set<std::string> & visited,
                   double value) {
  if(edge_weights[from].count(to)) return value * edge_weights[from][to];

  visited.insert(from);

  for (const std::pair<std::string, double> & edge : edge_weights[from]) {
    if (visited.count(edge.first) == 0) {
      double val = SeekWithDFS(edge.first, to, edge_weights, visited, value * edge.second);
      if (val != -1.0) {
        return val;
      }
    }
  }

  return -1.0;
}
};
