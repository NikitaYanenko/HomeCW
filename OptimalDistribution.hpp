#ifndef OPTIMAL_DISTRIBUTION_HPP
#define OPTIMAL_DISTRIBUTION_HPP

#include <vector>
#include <set>
#include <fstream>
#include <iostream>

#include "Server.hpp"

inline std::vector<Server> greedyDistribution(const std::vector<Server>& servers, int requests) {
    std::vector<Server> result = servers;

    for (int i = 0; i < requests; ++i) {
        int best = 0;
        for (int j = 1; j < result.size(); ++j) {
            if (result[j].effectiveLoad() < result[best].effectiveLoad())
                best = j;
        }
        result[best].load++;
    }

    return result;
}

inline std::vector<Server> treeBasedDistribution(const std::vector<Server>& servers, int requests) {
    std::set<Server> tree(servers.begin(), servers.end());

    for (int i = 0; i < requests; ++i) {
        auto best = *tree.begin();
        tree.erase(tree.begin());
        best.load++;
        tree.insert(best);
    }

    return std::vector<Server>(tree.begin(), tree.end());
}

inline void saveResultsToFile(std::string_view FILENAME, const std::vector<Server>& greedyServers, const std::vector<Server>& treeServers) {
    std::ofstream out(FILENAME.data());

    if (!out.is_open()) {
        std::cerr << "Error opening file: " << FILENAME << std::endl;
        return;
    }

    for (size_t i = 0; i < greedyServers.size(); ++i) {
        out << greedyServers[i].id << "," << greedyServers[i].load
            << "," << treeServers[i].load << std::endl;
    }

    std::cout << "Result saved to " << FILENAME << std::endl;
}
#endif // OPTIMAL_DISTRIBUTION_HPP