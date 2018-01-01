Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.

Examples: 

```
"123", 6 -> ["1+2+3", "1*2*3"] 
"232", 8 -> ["2*3+2", "2+3*2"]
"105", 5 -> ["1*0+5","10-5"]
"00", 0 -> ["0+0", "0-0", "0*0"]
"3456237490", 9191 -> []
```

# Solution

My first intuitive solution is to use divide and conquer. What I though is that we can just use a function which look like ``` vector<pair<string, int>> getItems(const string & str)```, this function will return a vector of expression string and their corresponding value. However, it is not easy to implement when the operators have different priorities. For example, you get one item <"1+2 * 3", 7> and another item<"4-5", -1>, how can to concatenate theses two strings with operator '\*' ? This means divide-and-conquer is not a good option for this problem.  

Because this problem only involes three operatos, '+', '-', '\*'. We can just keep calculating all possibilities and find out the results which meet our requirements. The only tricky thing here is how to handle '\*'. If we treat "+3", "-16", "-3\*2\*4" as segments, then we can make our calculation easier. "3 - 16 + 22" can be treated as a sum of "+3", "-16", "+22", "-4+17-3\*2\*4 " can be treated as a sum of "-4", "+17", "-3\*2\*4". In order to handle '\*' which concatenate multiple numbers together, we need stores value of previous number. 

This problem has a lot of edge cases to be considered:

* overflow: we use a long type once it is larger than Integer.MAX_VALUE or minimum, we get over it.
* 0 sequence: because we can't have numbers with multiple digits started with zero, we have to deal with it too.
* a little trick is that we should save the value that is to be multiplied in the next recursion.

The tricky part of this problem is that we need to treat "2\*4\*8" as a whole.

```cpp
class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> reval;
        string temp("");
        addOperatorWithDFS(reval, temp , num, target, 0, 0, 0);
        return reval;
    }
private:
    void addOperatorWithDFS(vector<string> &reval,
                            const string &temp,
                            const string &num,
                            const int target,
                            const std::size_t pos,
                            const long pre_num,
                            const long cur_val
                            ) {
        if (pos == num.size()) {
            if (cur_val == target) {
                reval.emplace_back(temp);
            }
        } else {
            for (std::size_t len = 1, n = num.size(); pos + len <= n; ++ len) {
                if (len > 1 && num[pos] == '0') break; // prevent "0x"
                const string &str = num.substr(pos, len);
                const long val = std::stol(str);
                
                if (temp.empty()) {
                    addOperatorWithDFS(reval, str, num, target, pos + len, val,  val);
                } else {
                    // add '*'
                    addOperatorWithDFS(reval, temp + '*' + str, num, target, 
                                        pos + len, pre_num * val, cur_val - pre_num + pre_num * val);
                    // add '+'
                    addOperatorWithDFS(reval, temp + '+' + str, num, target, 
                                        pos + len, val, cur_val + val);
                    // add '-'
                    addOperatorWithDFS(reval, temp + '-' + str, num, target, 
                                        pos + len, -val, cur_val - val);
                }
            }
        }
    }
};

```

# Knowledge

### Backtracking

Backtracking is a general algorithm for finding all (or some) solutions to some __computational problems__, notably __constraint satisfaction problems__, that incrementally builds candidates to the solutions, and abandons each partial candidate ("backtracks") as soon as it determines that the candidate cannot possibly be completed to a valid solution.


The classic textbook example of the use of backtracking is the eight queens puzzle, that asks for all arrangements of eight chess queens on a standard chessboard so that no queen attacks any other. In the common backtracking approach, the partial candidates are arrangements of k queens in the first k rows of the board, all in different rows and columns. Any partial solution that contains two mutually attacking queens can be abandoned.

Backtracking can be applied only for problems which admit the concept of a _"partial candidate solution"_ and a relatively quick test of whether it can possibly be completed to a valid solution. It is useless, for example, for locating a given value in an unordered table. When it is applicable, however, backtracking is often much faster than brute force enumeration of all complete candidates, since it can eliminate a large number of candidates with a single test.

Backtracking is an important tool for solving constraint satisfaction problems, such as crosswords, verbal arithmetic, Sudoku, and many other puzzles. It is often the most convenient (if not the most efficient[citation needed]) technique for parsing, for the knapsack problem and other combinatorial optimization problems. It is also the basis of the so-called logic programming languages such as Icon, Planner and Prolog.

Backtracking depends on user-given "black box procedures" that define the problem to be solved, the nature of the partial candidates, and how they are extended into complete candidates. It is therefore a metaheuristic rather than a specific algorithm – although, unlike many other meta-heuristics, it is guaranteed to find all solutions to a finite problem in a bounded amount of time.

The backtracking algorithm enumerates a set of _partial candidates_ that, in principle, could be completed in various ways to give all the possible solutions to the given problem. The completion is done incrementally, by a sequence of candidate extension steps.

Conceptually, the partial candidates are represented as the nodes of a tree structure, the _potential search tree_. Each partial candidate is the parent of the candidates that differ from it by a single extension step; the leaves of the tree are the partial candidates that cannot be extended any further.

The backtracking algorithm traverses this search tree recursively, from the root down, in depth-first order. At each node c, the algorithm checks whether c can be completed to a valid solution. If it cannot, the whole sub-tree rooted at c is skipped (pruned). Otherwise, the algorithm (1) checks whether c itself is a valid solution, and if so reports it to the user; and (2) recursively enumerates all sub-trees of c. The two tests and the children of each node are defined by user-given procedures.

Therefore, the actual search tree that is traversed by the algorithm is only a part of the potential tree. The total cost of the algorithm is the number of nodes of the actual tree times the cost of obtaining and processing each node. This fact should be considered when choosing the potential search tree and implementing the pruning test.
