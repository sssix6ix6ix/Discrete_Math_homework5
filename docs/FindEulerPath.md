# graphSolver::FindEulerianPath
The FindEulerianPath function is a member function of the graphSolver class that finds an Eulerian path in a graph using a depth-first search algorithm.

## Syntax
```
void graphSolver::FindEulerianPath(std::set<std::pair<std::string, std::string>>& used, std::vector<std::string>& path, std::string current);
```
## Parameters
used: A reference to a set of pairs of strings representing the edges of the graph that have already been visited.
path: A reference to a vector of strings representing the current path being constructed.
current: A string representing the current node being visited.
    Return Value
This function returns nothing (void), as it modifies the used and path parameters passed by reference.

## Algorithm
The FindEulerianPath function uses a depth-first search algorithm to find an Eulerian path. It visits all edges reachable from the current node, keeping track of which edges have been used by adding them to the used set. It then recursively calls itself on each unvisited edge, updating the path vector with the current node as it goes.

## Example Usage
```
// Create a graphSolver object and add edges to its graph
graphSolver solver;
solver.addEdge("Netherlands", "Belgium");
solver.addEdge("Belgium", "Germany");
solver.addEdge("Germany", "Austria");
solver.addEdge("Austria", "Italy");
solver.addEdge("Italy", "Greece");
solver.addEdge("Greece", "Turkey");


// Find and print the Eulerian path
std::vector<std::string> path;
std::set<std::pair<std::string, std::string>> used;
solver.FindEulerianPath(used, path, "Netherlands");
std::reverse(path.begin(), path.end());
for (const auto& country : path) {
std::cout << country << " -> ";
}
```
## Output:
```
Turkey -> Greece -> Italy -> Austria -> Germany -> Belgium -> Netherlands ->
```
# graphSolver::FindEulerPath
The FindEulerPath function is a member function of the graphSolver class that finds an Eulerian path in a graph and prints it out.

## Syntax
```
void graphSolver::FindEulerPath();
```
## Parameters
This function does not take any parameters.

## Return Value
This function returns nothing (void).

## Algorithm
The FindEulerPath function initializes the used and path parameters and then calls FindEulerianPath with the starting node "Netherlands". It then reverses the path vector and prints out each node in the path.

## Example Usage
```
// Create a graphSolver object and add edges to its graph
graphSolver solver;
solver.addEdge("Netherlands", "Belgium");
solver.addEdge("Belgium", "Germany");
solver.addEdge("Germany", "Austria");
solver.addEdge("Austria", "Italy");
solver.addEdge("Italy", "Greece");
solver.addEdge("Greece", "Turkey");

// Find and print the Eulerian path
solver.FindEulerPath();
```
## Output:
```
Turkey -> Greece -> Italy -> Austria -> Germany -> Belgium -> Netherlands ->
```