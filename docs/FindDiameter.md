## Description:
This function finds the diameter of the graph, which is the maximum distance between any two vertices in the graph. It uses the FindEccentricity() function to find the eccentricity of each vertex in the graph and then returns the vertex with the highest eccentricity as well as the corresponding eccentricity value.

## Signature:
```
std::pair<std::string, size_t> graphSolver::FindDiameter()
```

## Parameters:
``` This function takes no input parameters. ```

## Return Value:
This function returns a std::pair object containing the vertex with the highest eccentricity (std::string) and its corresponding eccentricity value (size_t).

## Example Usage:
To find the diameter of a graph using this function, call it on an instance of the graphSolver class. For example:

````
graphSolver solver;
std::pair<std::string, size_t> diameter = solver.FindDiameter();
std::cout << "The diameter of the graph is " << diameter.second << " and it passes through vertex " << diameter.first << std::endl;
````
This will output a message similar to the following:

```The diameter of the graph is 5 and it passes through vertex A```

## Notes:

This function assumes that the graph is stored in the graphSolver object using a std::map<std::string, std::vectorstd::string> data structure, where the keys of the map represent the vertices of the graph and the values of the map represent the neighboring vertices of each vertex.
This function uses the FindEccentricity() function to calculate the eccentricity of each vertex.


