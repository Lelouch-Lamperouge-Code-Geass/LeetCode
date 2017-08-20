Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

Note:
1. If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string. For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
2. All airports are represented by three capital letters (IATA code).
3. You may assume all tickets form at least one valid itinerary.

Example 1:  
```
tickets = [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Return ["JFK", "MUC", "LHR", "SFO", "SJC"].
```

Example 2:  
```
tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Return ["JFK","ATL","JFK","SFO","ATL","SFO"].
Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"]. But it is larger in lexical order.
```

# Knowledge

In graph theory, an __Eulerian trail__ (or __Eulerian path__) is a trail in a finite graph which visits __every edge exactly once__. Similarly, an __Eulerian circuit__ or __Eulerian cycle__ is an Eulerian trail which starts and ends on the same vertex. They were first discussed by Leonhard Euler while solving the famous Seven Bridges of Königsberg problem in 1736. The problem can be stated mathematically like this: "Given the graph in the image, is it possible to construct a path (or a cycle, i.e. a path starting and ending on the same vertex) which visits each edge exactly once?".

Euler proved that a necessary condition for the existence of __Eulerian circuits__ is that all vertices in the graph have an even degree, and stated without proof that connected graphs with all vertices of even degree have an Eulerian circuit. 

__Note : Eulerian Cycle and Eulerian Path are different !__


##### What is the difference between Euler cycle and Hamilton cycle?

A Euler path is a path that crosses __every edge__ exactly once without repeating, if it ends at the initial vertex then it is a Euler cycle.

A Hamiltonian path passes through __each vertex__ (note not each edge), exactly once, if it ends at the initial vertex then it is a Hamiltonian cycle.

In a Euler path you might pass through a vertex more than once.

In a Hamiltonian path you may not pass though all edges.


# Solution

Starting at the first node, we can only get stuck at the ending point, since every node except for the first and the last node has even number of edges, when we enter a node we can always get out. Now we are at the destination and if all edges are visited, we are done, and the dfs returns to the very first state. Otherwise we need to "insert" the unvisited loop into corresponding position, and in the dfs method, it returns to the node with extra edges, starts another recursion and adds the result before the next path. This process continues until all edges are visited.

```cpp
class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        // multiset<string> sort string by lexical order naturally
        std::unordered_map<std::string, std::multiset<std::string>> itineraries;
        for (const std::pair<std::string, std::string> &ticket : tickets) {
            itineraries[ticket.first].insert(ticket.second);
        }
        std::vector<std::string> route;
        visit("JFK", itineraries, route);
        return std::vector<std::string>(route.rbegin(), route.rend());
    }
    
private:
        void visit(const std::string &airport, 
                   std::unordered_map<std::string, std::multiset<std::string>> & itineraries,
                   std::vector<std::string> & route) {
            while(!itineraries[airport].empty()) {
                const std::string next = *itineraries[airport].begin();
                itineraries[airport].erase(itineraries[airport].begin());
                visit(next, itineraries, route);
            }
            
            route.push_back(airport);
        }
};
```
