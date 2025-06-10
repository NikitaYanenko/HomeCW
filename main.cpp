#include "LongestIncreasingSubsequence.hpp"
#include "Bank.hpp"
#include "OptimalDistribution.hpp"

int main() {
     //Task 1
    int operations = 2;
    std::vector<int> arrivals = { 1, 2, 3, 4, 5 };
    std::vector<int> services = { 2, 4, 2, 4, 2 };

    BankSystem::Bank bank(operations, arrivals, services);
    bank.run();

    // Task 2
    int requests = 12;
    int servers = 4;

    std::vector<int> performance = { 18, 22, 26, 30 };
    std::vector<int> load = { 7, 5, 3, 1 };

    std::vector<Server> greedyServers, treeServers;

    for (int i = 0; i < servers; ++i) {
        greedyServers.push_back({ i, load[i], performance[i] });
        treeServers.push_back({ i, load[i], performance[i] });
    }

    greedyServers = greedyDistribution(greedyServers, requests);
    treeServers = treeBasedDistribution(treeServers, requests);

    saveResultsToFile("serverLoad.txt", greedyServers, treeServers);

    // Task 3
    std::array<unsigned int, 5> nums = { 1, 3, 5, 7, 9 };
    int result = lengthOfLIS(nums);
    std::cout << "LIS length: " << result;

    return 0;
}