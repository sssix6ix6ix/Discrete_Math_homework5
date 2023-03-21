#ifndef GRAPHSOLVER_OPERATIONWITHSET_H
#define GRAPHSOLVER_OPERATIONWITHSET_H

#include <set>
#include <vector>
#include <string>
#include <iostream>

//A function that takes two sets as input and returns a set that is the union of the two sets.
std::set<std::string> SetUnion(const std::set<std::string>& lhs, const std::set<std::string>& rhs);

//Taking two sets and returning a set that is the intersection of the two sets.
std::set<std::string> SetIntersection(const std::set<std::string>& lhs, const std::set<std::string>& rhs);

//Taking two sets and returning a set that is the difference of the two sets.
std::set<std::string> SetDiffence(const std::set<std::string>& lhs, const std::set<std::string>& rhs);

//Converting a vector to a set.
std::set<std::string> VectorToSet(const std::vector<std::string>& vec);

#endif //GRAPHSOLVER_OPERATIONWITHSET_H
