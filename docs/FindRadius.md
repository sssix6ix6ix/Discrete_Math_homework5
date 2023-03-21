## Function Description
The FindRadius function calculates the radius of an undirected graph represented by an unordered map with keys as node names and values as vectors of adjacent node names. The radius of a graph is defined as the minimum eccentricity of any node in the graph.

The function returns a pair of values representing the node with the minimum eccentricity (i.e., the center of the graph) and the value of its eccentricity (i.e., the radius of the graph).

## Function Implementation
The function starts by creating a radius pair of values, where the first value represents the node with the minimum eccentricity, and the second value is set to INT_MAX, representing the initial maximum eccentricity of any node.

It then enters a loop that iterates over each node in the graph. For each node, the function calls the FindEccentricity function to calculate its eccentricity. If the eccentricity is less than the current minimum eccentricity (i.e., the value of radius.second), the function updates the radius pair to set the current node as the center of the graph (i.e., radius.first is set to the current node), and sets the new minimum eccentricity (i.e., radius.second is set to the eccentricity of the current node).

Once all nodes have been visited, the function returns the radius pair, which contains the center node and the radius of the graph.

## Function Usage

You can then call the FindRadius function to calculate the radius of the graph. The function will return a pair of values, where the first value is the node with the minimum eccentricity (i.e., the center of the graph), and the second value is the value of its eccentricity (i.e., the radius of the graph). Here is an example usage of the function:

````
graphSolver solver;
solver.graph = {
{"A", {"B", "C"}},
{"B", {"A", "C"}},
{"C", {"A", "B", "D"}},
{"D", {"C"}}
};

auto [center, radius] = solver.FindRadius();
std::cout << "The center of the graph is " << center << ", with a radius of " << radius << std::endl;
````
In this example, the graph represents a simple undirected graph with four nodes A, B, C, and D. The FindRadius function is called on this graph, and the center node and radius of the graph are printed to the console.