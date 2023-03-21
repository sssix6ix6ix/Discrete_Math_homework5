#include "OperationWithSet.h"

/**
 * "Return a set that contains all the elements of the first set and all the elements of the second set."
 *
 * Args:
 *   lhs (set<std::string>): The left hand side of the union.
 *   rhs (set<std::string>): The right hand side of the union.
 *
 * Returns:
 *   A set of strings.
 */
std::set<std::string> SetUnion(const std::set<std::string>& lhs, const std::set<std::string>& rhs) {
    std::set<std::string> tmp = lhs;

    for (const std::string& x : rhs) {
        tmp.insert(x);
    }

    return tmp;
}

/**
 * "For each element in the left hand side set, if it's also in the right hand side set, add it to the result set."
 *
 * Args:
 *   lhs (set<std::string>): The first set to intersect.
 *   rhs (set<std::string>): The right hand side of the intersection.
 *
 * Returns:
 *   A set of strings.
 */
std::set<std::string> SetIntersection(const std::set<std::string>& lhs, const std::set<std::string>& rhs) {
    std::set<std::string> tmp;

    for (const std::string& x : lhs) {
        if (rhs.count(x)) tmp.insert(x);
    }

    return tmp;
}

/**
 * Return a set containing all the elements of the first set that are not in the second set.
 *
 * Args:
 *   lhs (set<std::string>): The first set to compare.
 *   rhs (set<std::string>): The set to subtract from.
 *
 * Returns:
 *   A set of strings.
 */
std::set<std::string> SetDiffence(const std::set<std::string>& lhs, const std::set<std::string>& rhs) {
    std::set<std::string> tmp = lhs;

    for (const std::string& x : rhs) {
        tmp.erase(x);
    }

    return tmp;
};

///**
// * Convert a vector of strings to a set of strings.
// *
// * @param vec The vector to convert to a set.
// *
// * @return A set of strings.
// */
std::set<std::string> VectorToSet(const std::vector<std::string>& vec) {
    std::set<std::string> tmp;

    for (const std::string& x : vec) {
        tmp.insert(x);
    }

    return tmp;
}