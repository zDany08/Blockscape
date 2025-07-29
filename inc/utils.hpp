#ifndef UTILS_HPP
#define UTILS_HPP

#include <logger.hpp>
#include <string>
#include <random>
#include <fstream>
#include <vector>
#include <functional>
#include <utility>
#define GLFW_INCLUDE_NONE
#include <nlohmann/json.hpp>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

constexpr int windowWidth = 900;
constexpr int windowHeight = 600;

std::string getFileContent(std::ifstream&);

int randInt(int, int);

float randFloat(float, float);

extern bool focused;

extern bool fullscreen;

void enableFullscreen(GLFWwindow*);

void disableFullscreen(GLFWwindow*);

void toggleFullscreen(GLFWwindow*);

extern bool debugMode;

extern int fov;

extern int speed;

extern float sensitivity;

extern int renderDistance;

extern float lastTime;
extern float currentTime;
extern float deltaTime;

void calculateTime();

int width(GLFWwindow*);

int height(GLFWwindow*);

class Debug {
	public:
		Debug(GLFWwindow*);
		
		void begin();
		
		void render(std::string, std::function<void()>);
		
		void end();
		
		~Debug();
};

extern float fpsLastTime;
extern float fpsCurrentTime;
extern int frames;
extern int fps;

void calculateFps();

extern int dayLength;
extern float dayLastTime;
extern float dayCurrentTime;
extern int dayTime;

float getDayColor(float, float);

void calculateDayTime();

#endif
