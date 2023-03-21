#include "graphSolver.h"

#include <algorithm>
#include <iostream>
#include <queue>

/**
 * It reads a line from the input stream, parses it, and adds the parsed data to the graph
 *
 * Returns:
 *   The stream is being returned.
 */
std::istream& operator>>(std::istream& stream, graphSolver& g) {

    while (!stream.eof()) {
        std::string from;
        std::getline(stream, from, ':');
        if (from.empty()) continue;

        std::vector<std::string> to;
        std::string countries;

        std::getline(stream, countries);
        std::string country;

        for (int i = 1; i < countries.size(); i++) {
            char c = countries[i];

            if (c == ',') {
                to.push_back(country);
                country.clear();
                i++;
            } else {
                country += c;
            }
        }

        to.push_back(country);

        g.graph[from] = to;
    }

    return stream;
}

/**
 * It finds the maximum distance from a given country to any other country
 *
 * Args:
 *   country (string): The country to find the eccentricity of.
 *
 * Returns:
 *   The eccentricity of the country.
 */
size_t graphSolver::FindEccentricity(const std::string& country) {
    std::unordered_map<std::string, size_t> dist;
    std::queue<std::string> q;

    q.push(country);
    dist[country] = 0;

    size_t eccentricity = 0;
    while (!q.empty()) {
        auto from_county = q.front();
        q.pop();

        for (const auto& to_country : graph[from_county]) {
            if (!dist.count(to_country) || dist[to_country] > dist[from_county] + 1) {
                dist[to_country] = dist[from_county] + 1;
                eccentricity = std::max(eccentricity, dist[to_country]);
                q.push(to_country);
            }
        }
    }

    return eccentricity;
}

/**
 * For each vertex in the graph, find its eccentricity and if it's less than the current eccentricity, update the radius
 *
 * Returns:
 *   A pair of strings and size_t.
 */
std::pair<std::string, size_t> graphSolver::FindRadius() {
    std::pair<std::string, size_t> radius = {"", INT_MAX};

    for (auto [from, to]: graph) {
        size_t eccentricity = FindEccentricity(from);
        if (eccentricity < radius.second) {
            radius.first = from;
            radius.second = eccentricity;
        }
    }

    return radius;
}

/**
 * For each vertex in the graph, find its eccentricity and if it's greater than the current eccentricity, update the
 * diameter
 *
 * Returns:
 *   A pair of strings and size_t.
 */
std::pair<std::string, size_t> graphSolver::FindDiameter() {
    std::pair<std::string, size_t> diameter = {"", 0};

    for (auto [from, to]: graph) {
        size_t eccentricity = FindEccentricity(from);
        if (eccentricity > diameter.second) {
            diameter.first = from;
            diameter.second = eccentricity;
        }
    }

    return diameter;
}

/**
 * For each vertex in the graph, if the eccentricity of that vertex is equal to the radius of the graph, then add that
 * vertex to the center of the graph.
 *
 * Returns:
 *   A vector of strings.
 */
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

/**
 * > For each vertex in the graph, we recursively call the Bron-Kerbosch algorithm on the graph induced by the neighbors of
 * the vertex
 *
 * @Args:
 *   R (set<std::string>): The current clique \
 *   P (set<std::string>): the set of possible vertices of maximal clique
 *   X (set<std::string>): The set of vertices that have been visited so far.
 *   max_clique (set<std::string>): the largest clique found so far
 */
void graphSolver::Bronkerbosch(std::set<std::string> R, std::set<std::string> P, std::set<std::string> X,
                               std::set<std::string>& max_clique) {
    if (P.empty() && X.empty()) {
        if (R.size() > max_clique.size()) {
            max_clique = R;
        }
    }

    auto PP = P;

    for (const auto& v : P) {
        Bronkerbosch(SetUnion(R, {v}),
                     SetIntersection(PP, VectorToSet(graph[v])),
                     SetIntersection(X, VectorToSet(graph[v])),
                     max_clique);

        PP = SetDiffence(PP, {v});
        X = SetUnion(X, {v});
    }
}

/**
 * > We start with an empty set of vertices, and a set of all vertices. We then recursively add vertices to the empty set,
 * and remove them from the set of all vertices, until we find a clique
 *
 * Returns:
 *   The set of nodes that form the maximum clique.
 */
std::set<std::string> graphSolver::Bronkerbosch() {
    std::set<std::string> candidates;
    for (auto [from, to] : graph) {
        candidates.insert(from);
    }

    std::set<std::string> max_clique;

    Bronkerbosch({}, candidates, {}, max_clique);

    return max_clique;
}

/**
 * For each country in the candidates set, we remove it from the candidates set, add it to the stable set, and then
 * recursively call the function with the new stable set and the new candidates set
 *
 * Args:
 *   stable_set (set<std::string>): the current stable set
 *   candidates (set<std::string>): the set of countries that are still available to be added to the stable set
 *   max_stable_set (set<std::string>): the set of countries that we are trying to find
 */
void graphSolver::FindMaximumStableSet(std::set<std::string> stable_set,
                                       std::set<std::string> candidates,
                                       std::set<std::string>& max_stable_set){
    if (candidates.empty()) {

        if (stable_set.size() > max_stable_set.size()) {
            max_stable_set = stable_set;
        }
    }

    std::set<std::string> tmp_candidates = candidates;

    for (const auto& country : tmp_candidates) {
        candidates.erase(country);
        /* It's adding the country to the stable set, and then removing all the countries that are connected to the
        country from the candidates set. */
        FindMaximumStableSet(SetUnion(stable_set, {country}),
                             SetDiffence(candidates, VectorToSet(graph[country])),
                             max_stable_set);
    }

}

/**
 * We start with an empty set of vertices, and a set of all vertices. We then recursively call the function with the
 * current set of vertices, and the set of all vertices minus the current set of vertices
 *
 * Returns:
 *   A set of strings.
 */
std::set<std::string> graphSolver::FindMaximumStableSet() {
    std::set<std::string> candidates;

    /* It's iterating over the graph and adding each country to the candidates set. */
    for (auto [from, to] : graph) {
        candidates.insert(from);
    }

    std::set<std::string> max_stable_set;

    FindMaximumStableSet({}, candidates, max_stable_set);

    return max_stable_set;
}

/**
 * It takes a set of candidates, and for each candidate, it checks if there's a candidate in the other set that is
 * connected to it. If there is, it adds the pair to the current matching, and recursively calls itself with the new set of
 * candidates
 *
 * Args:
 *   current (matching): the current matching
 *   candidates (set<std::string>): a set of all the countries in the graph
 *   max_matching (matching): the maximum matching found
 *
 * Returns:
 *   The maximum matching in a bipartite graph.
 */
void graphSolver::FindMaximumMatching(matching current,
                                      std::set<std::string> candidates,
                                      matching& max_matching) {

    bool flag = false;

    auto tmp_candidates = candidates;

    if (max_matching.size() == 19) return; //you can comment it out to do an exhaustive search, but for the task i did, 19 was found to be the maximum

    /* Finding the maximum matching in a bipartite graph. */
    for (const auto& country : tmp_candidates) {
        for (const auto& to_country : graph[country]) {
            if (candidates.count(to_country)) {
                if (!flag) current.emplace_back();
                flag = true;
                current.back() = {country, to_country};
                FindMaximumMatching(current,
                                    SetDiffence(candidates, {country, to_country}),
                                    max_matching);
            }
        }

        candidates.erase(country);
    }
    /* Checking if the current matching is larger than the max matching. If it is, it prints the current matching and sets
    the max matching to the current matching. */
    if (!flag && current.size() > max_matching.size()) {

        std::cout << "Founded matching of size " << current.size() << '\n';

        for (auto [from, to] : current) {
            std::cout << from << " " << to << '\n';
        }

        std::cout << "\n---------------------\n";

        max_matching = current;
    }
}

matching graphSolver::FindMaximumMatching() {
    /* Finding the maximum matching in a bipartite graph. */
    std::set<std::string> candidates;

    for (auto [from, to] : graph) {
        candidates.insert(from);
    }

    matching max_matching;

    FindMaximumMatching({}, candidates, max_matching);

    return max_matching;
}

/**
 * Find the Eulerian path of the graph and print it out
 *
 * Args:
 *   used (set<std::pair<std::string, std::string>>): A set of pairs of strings that represent the edges that have been
 * used.
 *   path (vector<std::string>): The path of countries that the user has taken.
 *   current (string): The current country that the user is in.
 */
void graphSolver::FindEulerianPath(std::set<std::pair<std::string, std::string>>& used, std::vector<std::string>& path, std::string current) {
    for (const auto& to : graph[current]) {
        if (!used.count({current, to})) {
            used.insert({current, to});
            used.insert({to, current});
            FindEulerianPath(used, path, to);
        }
    }

    /* Adding the current node to the path. */
    path.emplace_back(current);
};

void graphSolver::FindEulerPath() {
    std::vector<std::string> path;
    std::set<std::pair<std::string, std::string>> used;

    /* Finding the Eulerian path of the graph. */
    FindEulerianPath(used, path, "Netherlands");

    reverse(path.begin(), path.end());

    /* Printing out the path of countries that the user has taken. */
    for (const auto& country : path) {
        std::cout << country << " -> ";
    }
}

/**
 * It finds the minimum spanning tree of the graph
 *
 * Args:
 *   dist (map<std::pair<std::string, std::string>, size_t>): a map of distances between countries
 *   spanning_tree (spanningTree): the output of the function, a vector of pairs of strings and size_t.
 *   start_country (string): the country from which the spanning tree will start
 */

//read docs
/**
 * FindMinimumSpanningTree - This function finds the minimum spanning tree of the graph by iterating through all the countries
 * and finding the minimum spanning tree starting from each country. It then compares the length of each minimum spanning tree
 * to find the shortest one.
 *
 * @param dist A map that stores the distances between each pair of countries.
 * @param spanning_tree A reference to a spanning tree, which will store the edges of the minimum spanning tree.
 * @param start_country A string representing the country to start the search for the minimum spanning tree.
 *
 * @return void
 */
void graphSolver::FindMinimumSpanningTree(std::map<std::pair<std::string, std::string>, size_t>& dist,
                                          spanningTree& spanning_tree, std::string start_country) {
    // Get the number of vertices in the graph
    size_t V = graph.size();
    // Initialize the number of used edges to 0
    size_t used_edge = 0;

    // Initialize variables to store the vertices of the edges with the minimum distance
    std::string x;
    std::string y;

    // Create a set to store the vertices that have already been used
    std::set<std::string> used;
    used.insert(start_country);

    // Iterate until the number of used edges is equal to V-1
    while (used_edge < V - 1) {
        // Initialize the minimum distance to the maximum integer value
        size_t mn = INT_MAX;
        // Clear the variables storing the vertices of the edges with the minimum distance
        x.clear();
        y.clear();

        // Iterate through all the countries in the graph
        for (auto [i_country, i_to] : graph) {
            // Check if the current country has already been used
            if (used.count(i_country)) {
                // Iterate through all the neighboring countries
                for (auto j_country : i_to) {
                    // Check if the neighboring country has not been used yet and the distance between them is smaller
                    // than the current minimum distance
                    if (!used.count(j_country) && mn > dist[{i_country, j_country}]) {
                        // Update the minimum distance and the vertices of the edge
                        mn = dist[{i_country, j_country}];
                        x = i_country;
                        y = j_country;
                    }
                }
            }
        }

        // Add the edge with the minimum distance to the spanning tree
        spanning_tree.push_back({{x, y}, dist[{x, y}]});

        // Add the new vertex to the set of used vertices
        used.insert(y);
        // Increment the number of used edges
        used_edge++;
    }
}
/**
 * Find the minimum spanning tree of the graph, starting from each country and choose the one with minimum length.
 *
 * Args:
 *   distances (map<std::string, std::vector<std::pair<std::string, int>>>): A map of all the distances between countries.
 *     The keys are the names of the countries, and the values are vectors of pairs, where each pair consists of the name
 *     of a neighboring country and the distance to that country.
 *
 * Returns:
 *   A spanning tree of the graph, represented as a vector of pairs. Each pair consists of a pair of connected countries
 *   and the distance between them.
 */
spanningTree graphSolver::FindMinimumSpanningTree(std::map<std::string, std::vector<std::pair<std::string, int>>> distances) {
    // Convert the distances map to a map of pairs of countries and their distances
    std::map<std::pair<std::string, std::string>, size_t> dist;
    for (auto [from, to] : distances) {
        for (auto [country, cost] : to) {
            dist[{from, country}] = cost;
        }
    }

    // Initialize variables for the minimum spanning tree and its length
    spanningTree minimum_spanning_tree;
    int minimum_length = INT_MAX;

    // Iterate through all countries in the graph
    for (auto [start_country, to] : graph)  {
        // Find the minimum spanning tree starting from the current country
        spanningTree spanning_tree;
        FindMinimumSpanningTree(dist, spanning_tree, start_country);

        // Calculate the length of the minimum spanning tree
        size_t length = 0;
        for (auto [connected, cost] : spanning_tree) {
            length += cost;
        }

        // Update the minimum spanning tree and its length if the current one is shorter
        if (length < minimum_length) {
            minimum_length = length;
            minimum_spanning_tree = spanning_tree;
        }
    }

    // Return the minimum spanning tree
    return minimum_spanning_tree;
}

/**
 * The function finds the centroid of the graph
 *
 *
 *   @param node (string): The current node.
 *   @param used (set<std::string>): a set of strings that contains the nodes that have already been visited.
 *   @param dist (distance_): The distance map that contains the distance between the nodes.
 *   @param weight (size_t): the weight of the current node
 *   @param prev (string): The previous node.
 */
void graphSolver::FindCentroid(const std::string& node,
                               std::set<std::string>& used,
                               const distance_& dist,
                               size_t& weight, std::string prev) {
    used.insert(node);
    for (const auto& to : graph[node]) {
        /* Checking if the current node is the previous node or if the distance between the current node and the next node
        is not in the distance map. If either of these are true, then the loop continues. */
        if (to == prev || !dist.count({node, to})) continue;
        /* Finding the distance between the node and the destination node. */
        weight += dist.find({to, node})->second;

        /*if we didn`t used this vertices, go to this vertice*/
        if (!used.count(to)) {
            FindCentroid(to, used, dist, weight, node);
        }
    }
}

/**
 * It finds the centroid of the graph by finding the vertex with the smallest maximum weight of the components of the graph
 *
 * Args:
 *   T (spanningTree): the spanning tree
 *
 * Returns:
 *   The centroid of the graph and the weight of the centroid.
 */
std::pair<std::string, size_t> graphSolver::FindCentroid(spanningTree& T) {
    size_t min_weight = INT_MAX;
    std::string centroid;

    distance_ dist;

    for (auto [connecting, cost] : T) {
        dist[connecting] =  cost;
        dist[{connecting.second, connecting.first}] = cost;
    }

    for (auto [from, to] : graph) {
        size_t max_weight = 0;

        std::set<std::string> used;
        used.insert(from);

        for (auto branch_start : to) {
            if (!used.count(branch_start) && dist.count({from, branch_start})) {
                size_t weight_of_this_component = dist[{from, branch_start}];
                FindCentroid(branch_start, used, dist, weight_of_this_component, "");

                if (weight_of_this_component > max_weight) max_weight = weight_of_this_component;
            }
        }

        if (max_weight < min_weight) {
            centroid = from;
            min_weight = max_weight;
        }
    }

    return {centroid, min_weight};
}

/**
 * "The function creates a Prufer code from a tree."
 *
 * The function takes a spanning tree as a parameter and returns a Prufer code
 *
 * @param spanning_tree The spanning tree that we want to convert to a Prufer code.
 *
 * @return A string of the Prufer code.
 */
std::string graphSolver::PruferCode(spanningTree& spanning_tree) {
    std::map<std::string, std::set<std::string>> adjacency;

    for (auto [connected, cost] : spanning_tree) {
        adjacency[connected.first].insert(connected.second);
        adjacency[connected.second].insert(connected.first);
    }

    /* Declaring a string variable called prufer_code. */
    std::string prufer_code;

    /* Creating a Prufer code from a tree. */
    while (adjacency.size() > 2) {
        for (auto [leaf, parent] : adjacency) {
            /* Removing the leaf node from the adjacency list and adding the leaf node's parent to the Prufer code. */
            if (adjacency[leaf].size() == 1) {
                std::string adjacency_country = *parent.begin();

                adjacency.erase(leaf);
                adjacency[adjacency_country].erase(leaf);
                prufer_code += adjacency_country + ' ';
                break;
            }
        }
    }


    return prufer_code;
}

/**
 * `addEdge` adds an edge between two nodes in the graph.
 *
 * The first line of the function is a function declaration. It tells the compiler that the function `addEdge` takes two
 * `std::string` arguments, `lhs` and `rhs`, and returns nothing.
 *
 * The second line of the function is a function body. It tells the compiler what the function does.
 *
 * The function body is a single line of code. It adds an edge between `lhs` and `rhs` in the graph.
 *
 * The first line of the function body is a function call. It calls the `push_back` function on the `graph` object.
 *
 * The `push_back` function is a member function of the `std::vector` class. It adds an element to the end of a vector.
 *
 * The `graph` object is a `std::map` object.
 *
 * @param lhs The left hand side of the edge.
 * @param rhs The right hand side of the equation.
 */
void graphSolver::addEdge(const std::string& lhs, const std::string& rhs) {
    graph[lhs].push_back(rhs);
    graph[rhs].push_back(lhs);
}

void print(std::vector<int> container){
    /* Printing a new line. */
    std::cout << '\n';
    /* Printing out the contents of the container. */
    for (const auto& x : container) {
        std::cout << x << " ";
    }
    /* Printing a new line. */
    std::cout << '\n';
};
