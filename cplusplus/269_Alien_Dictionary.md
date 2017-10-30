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

This is a __topological sorting__ problem.
The usual algorithms for topological sorting have running time linear in the number of nodes plus the number of edges, asymptotically, __O(V+E)__:

1. Kahn's algorithm
2. Depth-first search

First, build a degree map for each character in all the words:

```
w:0
r:0
t:0
f:0
e:0
```

Then build the hashmap by comparing the adjacent words, the first character that is different between two adjacent words reflect the lexicographical order. For example:

```
 "wrt",
 "wrf",
    first different character is 3rd letter, so t comes before f

 "wrf",
 "er",
    first different character is 1rd letter, so w comes before e
 ```
 
 The characters in set come after the key. x->y means letter x comes before letter y. x -> set: y,z,t,w means x comes before all the letters in the set. The final HashMap "map" looks like.
 
```
t -> set: f    
w -> set: e
r -> set: t
e -> set: r
```

and final HashMap "degree" looks like, the number means "how many letters come before the key":

```
w:0
r:1
t:1
f:1
e:1
```

Then use Karn's aglorithm to do topological sort. This is essentially BFS.  
https://en.wikipedia.org/wiki/Topological_sorting  

首先必须要做的是需要找到局部的order，也就是前后单词字母比较给出的信息，以上面的例子来说，比较“wrt”和“wrf”就可以得到‘t’在‘f’之前的局部order。每一对这样前后的单词，至多产生一组这样的order，因为也可能得不到任何局部的order，比如“ab”和“abc”，这样就不能得出任何局部order了，需要注意这样的edge case。

然后有了这些order，我们需要整理出全局的order，这里需要一点抽象能力和经验，因为这个order本质是一种sort，而这种partial order的整理其实可以用topological sort解决。换句话说，我们把用到的字母当成node，之前得到的局部order当成directed edge，以此来建graph，然后利用topological sort来整理出全局order。想到这里就基本完成了，至于topological sort是用bfs还是dfs就看个人喜好了。

具体实现的话还是有些小技巧值得一提，因为我们需要保存order，也就是edge list，会自然想到用list或者map一类的数据结构。这点来说本身是没有问题的，因为这样很规范，也很适用于大部分情况，但是考虑到现在我们只有26个字母需要考虑，利用array来存储和更新数据会更加迅速轻巧。


### Kahn's algorithm

##### C++ solution

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

##### Java solution

```java
public String alienOrder(String[] words) {
    Map<Character, Set<Character>> map=new HashMap<Character, Set<Character>>();
    Map<Character, Integer> degree=new HashMap<Character, Integer>();
    String result="";
    if(words==null || words.length==0) return result;
    for(String s: words){
        for(char c: s.toCharArray()){
            degree.put(c,0);
        }
    }
    for(int i=0; i<words.length-1; i++){
        String cur=words[i];
        String next=words[i+1];
        int length=Math.min(cur.length(), next.length());
        for(int j=0; j<length; j++){
            char c1=cur.charAt(j);
            char c2=next.charAt(j);
            if(c1!=c2){
                Set<Character> set=new HashSet<Character>();
                if(map.containsKey(c1)) set=map.get(c1);
                if(!set.contains(c2)){
                    set.add(c2);
                    map.put(c1, set);
                    degree.put(c2, degree.get(c2)+1);
                }
                break;
            }
        }
    }
    Queue<Character> q=new LinkedList<Character>();
    for(char c: degree.keySet()){
        if(degree.get(c)==0) q.add(c);
    }
    while(!q.isEmpty()){
        char c=q.remove();
        result+=c;
        if(map.containsKey(c)){
            for(char c2: map.get(c)){
                degree.put(c2,degree.get(c2)-1);
                if(degree.get(c2)==0) q.add(c2);
            }
        }
    }
    if(result.length()!=degree.size()) return "";
    return result;
}
```

### DFS

__When using DFS to do topological sorting, it is important to check whethere there is a cycle in the graph.__

```cpp
class Solution {
private:
    typedef unordered_map<char, unordered_set<char>> Graph;
    
    Graph make_graph(vector<string>& words) {
        Graph g;
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
    
    // Return false if there is a cycle
    bool DFS(const Graph &graph,
            std::unordered_set<char> &visited,
            std::unordered_set<char> &in_dfs_cycle,
            std::ostringstream &oss,
            const char c) {
        if (in_dfs_cycle.count(c) != 0) return false;
        if (visited.count(c) == 0) {
            visited.insert(c);
            in_dfs_cycle.insert(c);
            
            for (const char to : graph.at(c)) {
                if (!DFS(graph, visited, in_dfs_cycle, oss, to)) return false;
            }
            
            in_dfs_cycle.erase(c);
            oss << c;
        }
        return true;
    }
public:
    string alienOrder(vector<string>& words) {
        if (words.size() == 1) return words[0];
        const Graph &graph = make_graph(words);
        
        std::unordered_set<char> visited, in_dfs_cycle;
        std::ostringstream oss;
        for (auto pair : graph) {
            const char c = pair.first;
            
            if (visited.count(c) == 0) {
                if (!DFS(graph, visited, in_dfs_cycle, oss, c)) return "";
            }
        }
        
        std::string reval = oss.str();
        std::reverse(reval.begin(), reval.end());
        
        return reval;
    }

};
```

# Summary

In the field of computer science, a topological sort or topological ordering of a directed graph is a linear ordering of its vertices such that for every directed edge uv from vertex u to vertex v, u comes before v in the ordering. For instance, the vertices of the graph may represent tasks to be performed, and the edges may represent constraints that one task must be performed before another; in this application, a topological ordering is just a valid sequence for the tasks. A topological ordering is possible if and only if the graph has no directed cycles, that is, if it is a directed acyclic graph (DAG). Any DAG has at least one topological ordering, and algorithms are known for constructing a topological ordering of any DAG in linear time.

### Algorithms

The usual algorithms for topological sorting have running time linear in the number of nodes plus the number of edges, asymptotically,  O(V+E).

1. Kahn's algorithm
2. An alternative algorithm for topological sorting is based on depth-first search. The algorithm loops through each node of the graph, in an arbitrary order, initiating a depth-first search that terminates when it hits any node that has already been visited since the beginning of the topological sort or the node has no outgoing edges.

##### Kahn's algorithm vs BFS

Thus the "queue" for topological sorting is really "any collection" structure and the ordering in this collection does not matter; it can be anything. The queue used for BFS on the other hand, is all about the order; so that it can accomplish its FIFO (first-in, first-out) task. Changing this ordering will ruin the BFS algorithm.

