This is the documentation for the FindMaximumMatching function in the graphSolver class. The function finds the maximum matching in a bipartite graph using a recursive algorithm.

## Function Signature
```
void graphSolver::FindMaximumMatching(matching current, std::set<std::string> candidates, matching& max_matching)
matching: an alias for std::vector<std::pair<std::string, std::string>>, a vector of pairs representing the current matching in the bipartite graph.
current: the current matching in the bipartite graph.
candidates: a set of candidate countries for the matching.
max_matching: a reference to the maximum matching found so far.
```
## Function Description
The FindMaximumMatching function takes in the current matching, a set of candidate countries, and a reference to the maximum matching found so far. The function finds the maximum matching in a bipartite graph using a recursive algorithm.

The function first initializes a flag variable to false. It then appends an empty pair to the current matching to represent a potential match. It creates a copy of the candidate countries and stores it in tmp_candidates.

The function then loops over each country in tmp_candidates and checks if there is an edge between the country and any country in its adjacency list. If there is, the function sets the flag variable to true, updates the last pair in the current matching to represent the match, and recursively calls itself with the updated matching and the remaining candidate countries.

After the loop, the function removes the current country from the set of candidate countries.

If there were no matches found in the loop and the current matching is larger than or equal to the maximum matching found so far, the function prints the current matching and updates the maximum matching to the current matching. The function then removes the last pair from the current matching and returns.

## Example Usage
```
graphSolver solver;

matching current_matching;
std::set<std::string> candidates = {"USA", "Canada", "Mexico"};
matching max_matching;

solver.FindMaximumMatching(current_matching, candidates, max_matching);
```
In this example, FindMaximumMatching is called with an empty current matching, a set of candidate countries, and a reference to an empty maximum matching. The function finds the maximum matching in the bipartite graph and updates the maximum matching reference.