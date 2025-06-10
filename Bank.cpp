#include "Bank.hpp"

namespace BankSystem {


    Bank::Bank(int operations, const std::vector<int>& arrivals, const std::vector<int>& services)
        : operators(operations), arrivalsT(arrivals), servicesT(services), totalClients(arrivals.size()) {
        logger->log("Bank created with " + std::to_string(operations) + " operators");
    }

	void BankSystem::Bank::clientProcess(int clientId) {
        std::this_thread::sleep_for(std::chrono::seconds(arrivalsT[clientId - 1]));

        {
            std::lock_guard lock(queueMutex);
            clientsQueue.push(clientId);
            logger->log("Client " + std::to_string(clientId) + " arrived");
        }

		operators.acquire();

        {
            std::lock_guard lock(queueMutex);
            int client = clientsQueue.front();
            clientsQueue.pop();
            logger->log("Client service " + std::to_string(client) + " started");
        }

        std::this_thread::sleep_for(std::chrono::seconds(servicesT[clientId - 1]));

        {
            std::lock_guard lock(queueMutex);
            logger->log("Client service " + std::to_string(clientId) + " completed");
            servedClients++;
        }

        operators.release();

	}

	void BankSystem::Bank::run() {
		std::vector<std::thread> clientsThreads;

		for (int i = 1; i <= totalClients; ++i) {
			clientsThreads.emplace_back(&Bank::clientProcess, this, i);
		}

		for (auto& client : clientsThreads) {
			client.join();
		}

        logger->log("Total served: " + std::to_string(servedClients) + " clients");
	}
}