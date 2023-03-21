#graphSolver::PruferCode(spanningTree& spanning_tree)

This function takes an object of type spanningTree, representing the spanning tree of a graph, as input. It returns a string containing the Prufer code for this tree.
```
std::map<std::string, std::setstd::string> adjacency;
```
This declaration creates an empty map adjacency, which will be used to store the adjacency list of the graph.

```
for (auto [connected, cost] : spanning_tree) {
adjacency[connected.first].insert(connected.second);
adjacency[connected.second].insert(connected.first);
}
```

This loop populates the adjacency list by iterating over each edge in the spanning tree and adding the appropriate vertices to the corresponding adjacency sets.
```
std::string prufer_code;
```
This declaration creates an empty string called prufer_code, which will be used to store the Prufer code.
```
while (adjacency.size() > 2) {
    for (auto [leaf, parent] : adjacency) {
        if (adjacency[leaf].size() == 1) {
            std::string adjacency_country = *parent.begin();
            adjacency.erase(leaf);
            adjacency[adjacency_country].erase(leaf);
            prufer_code += adjacency_country + ' ';
            break;
        }
    }
}
```
This loop constructs the Prufer code by repeatedly removing leaf nodes from the adjacency list and appending their parent nodes to the code. The loop terminates when only two nodes remain in the adjacency list.
```
return prufer_code;
```
This statement returns the completed Prufer code as a string.