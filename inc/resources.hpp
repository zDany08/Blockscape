#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <utils.hpp>

extern std::string resourcesPath;

class Resource {
public:
	std::string path;

	Resource(std::string);

	std::string toText();

	unsigned char* toImage(int*, int*);
};

nlohmann::json toJson(std::string);

std::string toText(nlohmann::json);

bool hasKey(nlohmann::json, std::string);

template<typename T>
bool hasValue(nlohmann::json json, T type) {
	for (T t : json.array()) if (t == type) return true;
	return false;
}

#endif
