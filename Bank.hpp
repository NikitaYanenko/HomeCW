#ifndef BANK_HPP
#define BANK_HPP

#include <vector>
#include <queue>
#include <semaphore>
#include <mutex>
#include <thread>

#include "Logger.hpp"

namespace BankSystem {

	class Bank {
	private:
		static inline auto* logger = BankLogger::BankLog::getInstance("BankSimulation.log");
		std::counting_semaphore<> operators;
		std::mutex queueMutex{};

		std::vector<int> arrivalsT;
		std::vector<int> servicesT;

		std::queue<int, std::deque<int>> clientsQueue{};

		int servedClients{0};
		int totalClients;
		
		void clientProcess(int clientId);
	public:
		Bank(int operations, const std::vector<int>& arrivals, const std::vector<int>& services);
		~Bank() = default;

		void run();
	};
}
#endif // !BANK_HPP