#include "Logger.hpp"

namespace BankLogger {

    Logger::Logger(std::string_view FILENAME, std::string_view timeFormat)
        : logFile(new std::ofstream(FILENAME.data()), LoggerUtility::FileDeleter()),
        timeFormat(timeFormat) {

        if (!logFile->is_open()) {
            std::cerr << "Error opening log file: " << FILENAME << std::endl;
        }

        log("----- Banking simulation started -----");
    }

    Logger::~Logger() {
        log("----- Banking simulation stopped -----");

    }

    void Logger::log(const std::string& logMessage) {
        std::lock_guard<std::mutex> lock(logMutex);
        const std::string logEntry = formatTime() + " " + logMessage;

        if (logFile->is_open()) {
            *logFile << logEntry << std::endl;
        }
    }

    std::string Logger::formatTime() const {
        auto now = std::chrono::system_clock::now();
        auto inTimeT = std::chrono::system_clock::to_time_t(now);
        std::tm tm{};

        if (localtime_s(&tm, &inTimeT) != 0) {
            return "[time_error]";
        }

        std::stringstream ss;
        ss << std::put_time(&tm, timeFormat.data());
        return ss.str();
    }
}