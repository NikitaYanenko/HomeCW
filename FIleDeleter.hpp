#ifndef FILE_DELETER_HPP
#define FILE_DELETER_HPP

#include <fstream>
#include <memory>
#include <iostream>

namespace LoggerUtility {

	struct FileDeleter {
		void operator()(std::ofstream* file) const {
			if (file && file->is_open()) {
				file->close();
			}
			delete file;
		}
	};

	using filePtr = std::unique_ptr<std::ofstream, FileDeleter>;
}

#endif // !FILE_DELETER_HPP