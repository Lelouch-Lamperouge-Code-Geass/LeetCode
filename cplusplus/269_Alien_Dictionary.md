There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You receive a list of words from the dictionary, wherewords are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.

For example,
Given the following words in dictionary,

```
[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]
```

The correct order is: "wertf".

Note:

* You may assume all letters are in lowercase.
* If the order is invalid, return an empty string.
* There may be multiple valid order of letters, return any one of them is fine.


# Solution

首先必须要做的是需要找到局部的order，也就是前后单词字母比较给出的信息，以上面的例子来说，比较“wrt”和“wrf”就可以得到‘t’在‘f’之前的局部order。每一对这样前后的单词，至多产生一组这样的order，因为也可能得不到任何局部的order，比如“ab”和“abc”，这样就不能得出任何局部order了，需要注意这样的edge case。

然后有了这些order，我们需要整理出全局的order，这里需要一点抽象能力和经验，因为这个order本质是一种sort，而这种partial order的整理其实可以用topological sort解决。换句话说，我们把用到的字母当成node，之前得到的局部order当成directed edge，以此来建graph，然后利用topological sort来整理出全局order。想到这里就基本完成了，至于topological sort是用bfs还是dfs就看个人喜好了。

具体实现的话还是有些小技巧值得一提，因为我们需要保存order，也就是edge list，会自然想到用list或者map一类的数据结构。这点来说本身是没有问题的，因为这样很规范，也很适用于大部分情况，但是考虑到现在我们只有26个字母需要考虑，利用array来存储和更新数据会更加迅速轻巧。

```cpp
class Solution {
public:
    string alienOrder(vector<string>& words) {
        if (words.size() == 1) return words[0];
        graph g = make_graph(words);
        unordered_map<char, int> degrees = compute_indegree(g);
        int numNodes = degrees.size();
        string order;
        queue<char> toVisit;
        for (auto node : degrees)
            if (!node.second)
                toVisit.push(node.first);
        for (int i = 0; i < numNodes; i++) {
            if (toVisit.empty()) return "";
            char c = toVisit.front();
            toVisit.pop();
            order += c;
            for (char neigh : g[c])
                if (!--degrees[neigh])
                    toVisit.push(neigh);
        }
        return order;
    }
private:
    typedef unordered_map<char, unordered_set<char>> graph;
    
    graph make_graph(vector<string>& words) {
        graph g;
        int n = words.size();
        for (int i = 1; i < n; i++) {
            bool found = false;
            string word1 = words[i - 1], word2 = words[i];
            int l1 = word1.length(), l2 = word2.length(), l = max(l1, l2);
            for (int j = 0; j < l; j++) {
                if (j < l1 && g.find(word1[j]) == g.end())
                    g[word1[j]] = unordered_set<char>();
                if (j < l2 && g.find(word2[j]) == g.end())
                    g[word2[j]] = unordered_set<char>();
                if (j < l1 && j < l2 && word1[j] != word2[j] && !found) {
                    g[word1[j]].insert(word2[j]);
                    found = true;
                }
            }
        }
        return g; 
    }
    
    unordered_map<char, int> compute_indegree(graph& g) {
        unordered_map<char, int> degrees;
        for (auto adj : g) {
            if (!degrees[adj.first]);
            for (char neigh : adj.second)
                degrees[neigh]++;
        }
        return degrees;
    }
};
```
