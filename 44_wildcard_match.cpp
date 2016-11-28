/* Solution 1 with dynamic programming */
class Solution {
public:
    bool isMatch(string s, string p) {
        const int s_size(s.size()), p_size(p.size());
        vector< vector<bool> > is_match(s_size+1, vector<bool>(p_size+1,false) );
        is_match[0][0] = true;
        for (int i=1;i<=p_size && p[i-1]=='*' ;++i) is_match[0][i] = true;
        
        for (int i=1;i<=s_size;++i) {
            for (int j=1;j<=p_size;++j) {
                if (p[j-1]!='*') {
                    is_match[i][j] = is_match[i-1][j-1] && (p[j-1]=='?' || s[i-1]==p[j-1]);
                } else {
                    is_match[i][j] = is_match[i][j-1]
                        || is_match[i-1][j-1]
                        || is_match[i-1][j] ;
                }
            }
        }
        return is_match[s_size][p_size];
    }
};

/* Solution 2 */
class Solution {
public:
    bool isMatch(string s, string p) {
        int si(0), pi(0),s_size(s.size()), p_size(p.size());
        int p_mark(-1),s_mark(-1);
        while (si<s_size) {
            if (p[pi]=='*') {
                // mark the index of wildcard and corresponding index in s
                p_mark = pi;
                s_mark = si;
                
                ++ pi; // * match 0 char at first shot
            } else {
                if (p[pi]=='?' || p[pi]==s[si]) {
                    ++ pi;
                    ++ si;
                } else {
                    if (p_mark!=-1) {
                        pi = p_mark + 1; //p_mark always point to wildcard index in p
                        si = s_mark+1; 
                        
                        ++ s_mark; // use '*' to match one char in s 
                    } else {
                        return false;
                    }    
                }
            }
        }
        
        while (pi<p_size && p[pi]=='*') ++pi; // p may have trailing *
        
        return si == s_size && pi == p_size;
    }
};
