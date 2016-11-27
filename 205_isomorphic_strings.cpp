class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() !=t.size()) return false;
        vector<int> s_mapper(256,-1), t_mapper(256,-1);
        const int str_size(s.size());
        for (int i=0;i<str_size;++i) {
            if (s_mapper[s[i]] != t_mapper[t[i]]) return false;
            s_mapper[s[i]] = t_mapper[t[i]] = i;
        }
        return true;
    }
};
