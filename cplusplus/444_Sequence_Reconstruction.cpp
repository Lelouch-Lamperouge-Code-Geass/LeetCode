// https://en.wikipedia.org/wiki/Topological_sorting#Uniqueness

bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
  if(seqs.empty()) return false;
  vector<int> pos(org.size()+1);
  const std::size_t org_size(org.size());
  for(std::size_t i = 0; i < org_size; ++i) {
    pos[org[i]] = i;
  }

  vector<char> flags(org_size + 1,0); // neighbor pairs
  int toMatch = org_size - 1;
  for(const auto& v : seqs) {
    for(std::size_t i=0;i < v.size();++i) {
      if(v[i] <= 0 || v[i] > org_size)return false;
      if(i == 0) continue;
      int x = v[i-1], y = v[i];
      if(pos[x] >= pos[y]) return false;
      if(flags[x] == 0 && pos[x]+1 == pos[y]) flags[x] = 1, --toMatch;
    }
  }
  return toMatch == 0;
}
