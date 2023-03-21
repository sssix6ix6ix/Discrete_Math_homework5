#ifndef GRAPHSOLVER_GRAPHSOLVER_H
#define GRAPHSOLVER_GRAPHSOLVER_H

#define matching std::vector<std::pair<std::string,std::string>>
#define spanningTree std::vector<std::pair<std::pair<std::string, std::string>, size_t>>
#define distance_ std::map<std::pair<std::string, std::string>, size_t>

#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <set>
#include <fstream>
#include "OperationWithSet.h"

//This is a class that is used to solve different graph problems.
class graphSolver {
public:
    std::unordered_map<std::string, std::vector<std::string>> graph;
    std::unordered_map<std::string, size_t> index_of;

    size_t FindEccentricity(const std::string& country);

    std::pair<std::string, size_t> FindRadius();

    std::pair<std::string, size_t> FindDiameter();

    std::vector<std::string> FindCenter();

    std::set<std::string> Bronkerbosch();

    void Bronkerbosch(std::set<std::string> R, std::set<std::string> P, std::set<std::string> X,
                      std::set<std::string>& max_clique);

    void FindMaximumStableSet(std::set<std::string> stable_set,
                              std::set<std::string> candidates,
                              std::set<std::string>& max_stable_set);

    std::set<std::string> FindMaximumStableSet();

    void FindMaximumMatching(matching current,
                             std::set<std::string> candidates,
                             matching& max_matcing);

    std::vector<std::pair<std::string,std::string>> FindMaximumMatching();

    std::set<std::string> FindMinimumVertexCover();

    void FindMinimumVertexCover(std::set<std::string> current_vertex_cover,
                                std::set<std::string> candidates,
                                std::set<std::string>& minimum_vertex_cover);

    void FindEulerPath();

    void FindEulerianPath(std::set<std::pair<std::string, std::string>>& used, std::vector<std::string>& path, std::string current);

    void FindMinimumSpanningTree(std::map<std::pair<std::string, std::string>, size_t>& dist,
                                 spanningTree& spanning_tree, std::string start_country);

    std::vector<std::pair<std::pair<std::string, std::string>, size_t>>
    FindMinimumSpanningTree(std::map<std::string, std::vector<std::pair<std::string, int>>> distances);

    void FindCentroid(const std::string& node,
                      std::set<std::string>& used,
                      const distance_& dist,
                      size_t& weight,
                      std::string prev = "");

    std::pair<std::string, size_t> FindCentroid(spanningTree& T);

    std::string PruferCode(spanningTree& spanning_tree);

    void addEdge(const std::string& lhs, const std::string& rhs);
};

void print(std::vector<int> container);


std::istream& operator>>(std::istream&, graphSolver& g);
#endif //GRAPHSOLVER_GRAPHSOLVER_H
