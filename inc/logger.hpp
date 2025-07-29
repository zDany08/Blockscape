#ifndef LOGGER_HPP
#define LOGGER_HPP

#pragma once

#include <iostream>

enum LogType {

	INFO,
	WARN,
	ERROR
};

void log(LogType, std::string);

void info(std::string);

void warn(std::string);

void error(std::string);

#endif
