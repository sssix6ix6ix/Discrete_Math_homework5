## Function Description
This function is a member function of the graphSolver class that returns a std::vector of std::string containing the center of the graph. The center of the graph is defined as the set of nodes whose eccentricity is equal to the radius of the graph.

## Parameters
This function takes no parameters.

## Return Value
This function returns a std::vector of std::string containing the center of the graph.

## Code Description
```
std::vector<std::string> graphSolver::FindCenter() {
size_t radius = FindRadius().second;
std::vector<std::string> center;

    for (const auto& [from, to] : graph) {
        if (FindEccentricity(from) == radius) {
            center.emplace_back(from);
        }
    }

    return center;
}
```

The function FindRadius() is called to get the radius of the graph, which is stored in the second element of the returned pair.    
A std::vector of std::string named center is declared to store the nodes in the center of the graph.  
A loop is iterated over all edges in the graph. The loop uses structured bindings to unpack each edge into the from and to nodes.  
The function FindEccentricity() is called for the from node to get its eccentricity.  
If the eccentricity of the from node is equal to the radius of the graph, the from node is added to the center vector using emplace_back().  
Once all nodes have been checked, the center vector is returned.  

## Example Usage
````
graphSolver gs;
// Add nodes and edges to the graph
// ...

// Get the center of the graph
std::vector<std::string> center = gs.FindCenter();

// Print the center nodes
std::cout << "The center nodes are: ";
for (const auto& node : center) {
std::cout << node << " ";
}
std::cout << std::endl;
````
In this example, an instance of the graphSolver class is created and nodes and edges are added to the graph. The FindCenter() function is called to get the center of the graph, and the resulting vector of strings is printed to the console.