## Introduction
The graphSolver::Bronkerbosch function is an implementation of the Bron-Kerbosch algorithm, a well-known algorithm for finding the maximum clique in an undirected graph. The algorithm takes three sets of vertices as input: a set of vertices R that have been selected to be part of the current clique, a set of vertices P that are candidates to be added to the clique, and a set of vertices X that have already been excluded from consideration. The algorithm recursively explores the graph by selecting a vertex v from P, adding it to R, and then recursively calling itself with updated sets of R, P, and X. The algorithm terminates when P and X are both empty, indicating that the current R is a maximal clique.

## Function signature
```
void graphSolver::Bronkerbosch(std::set<std::string> R, std::set<std::string> P, std::set<std::string> X,
std::set<std::string>& max_clique)
Parameters
R: a set of vertices that have been selected to be part of the current clique
P: a set of vertices that are candidates to be added to the clique
X: a set of vertices that have already been excluded from consideration
max_clique: a reference to the set of vertices that form the maximum clique found so far
```

## Return value
``` void ```

## Function description

The graphSolver::Bronkerbosch function implements the Bron-Kerbosch algorithm as described above. The algorithm is implemented using recursion, with each recursive call updating the sets of R, P, and X based on the current vertex v. The function also maintains a reference to the maximum clique found so far, updating it whenever a new maximal clique is found.


## Example usage
To use the graphSolver::Bronkerbosch function to find the maximum clique in a graph, one can call the function with an empty R set, a set of all vertices in the graph as the P set, an empty X set, and a reference to an empty max_clique set. The function will return the maximum clique found.

````
// Create a graph
std::map<std::string, std::vector<std::string>> graph = {
{"A", {"B", "C"}},
{"B", {"A", "C"}},
{"C", {"A", "B", "D"}},
{"D", {"C"}}
};

// Create a graphSolver object
graphSolver solver(graph);

// Find the maximum clique
std::set<std::string> max_clique = solver.Bronkerbosch();

// Print the maximum clique
std::cout << "Maximum clique: ";
for (const auto& node : max_clique) {
std::cout << node << " ";
}
std::cout << std::endl;
````

## Output:

```
Maximum clique: B C A
```

In this example, the maximum clique in the graph is B, C, and A. The graphSolver::Bronkerbosch function correctly identifies this clique and returns it as a set of vertex labels.
