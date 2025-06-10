#ifndef LOGGER_HPP 
#define LOGGER_HPP

#include <string>
#include <string_view>
#include <mutex>
#include <chrono>

#include "FileDeleter.hpp"
#include "Singleton.hpp"

namespace BankLogger {

	class Logger {
	private:
		LoggerUtility::filePtr logFile;
		std::mutex logMutex;
		std::string_view timeFormat;

		std::string formatTime() const;
	public:
		explicit Logger(std::string_view FILENAME, std::string_view timeFormat = "[%Y-%m-%d %H:%M:%S]");
		~Logger();

		void log(const std::string& logMessage);

	};

	using BankLog = Singleton<Logger>;
}
#endif // LOGGER_HPP