#include <logger.hpp>

void log(LogType type, std::string message) {
	switch (type) {
		case INFO:
			std::cout << "[INFO]: " << message << std::endl;
			break;
		case WARN:
			std::clog << "[WARN]: " << message << std::endl;
			break;
		case ERROR:
			std::cerr << "[ERROR]: " << message << std::endl;
			break;
	}
}

void info(std::string message) {
	log(INFO, message);
}

void warn(std::string message) {
	log(WARN, message);
}

void error(std::string message) {
	log(ERROR, message);
}
