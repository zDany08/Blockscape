#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <resources.hpp>

std::string resourcesPath = "res/";

Resource::Resource(std::string path_) : path(path_) {}

std::string Resource::toText() {
	std::ifstream file(resourcesPath + path);
	return getFileContent(file);
}

unsigned char* Resource::toImage(int* width, int* height) {
	int channels;
	return stbi_load((resourcesPath + path).c_str(), width, height, &channels, 4);
}

nlohmann::json toJson(std::string text) {
	return nlohmann::json::parse(text);
}

std::string toText(nlohmann::json json) {
	return nlohmann::to_string(json);
}

bool hasKey(nlohmann::json json, std::string key) {
	if (json.contains(key)) return true;
	return false;
}
