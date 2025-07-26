#include <utils.hpp>

std::string getFileContent(std::ifstream& file) {
	if(!file.is_open()) {
		std::cerr << "Error opening a file" << std::endl;
		return "";
	}
	std::string line, content;
	while(std::getline(file, line)) content = content.append(line).append("\n");
	return content;
}

int randInt(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distrib(min, max);
	return distrib(gen);
}

float randFloat(float min, float max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distrib(min, max);
	return distrib(gen);
}

bool focused = true;

bool fullscreen = false;

void enableFullscreen(GLFWwindow* window) {
	fullscreen = true;
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);
	glfwSetWindowMonitor(window, monitor, 0, 0, vidMode->width, vidMode->height, GLFW_DONT_CARE);
}

void disableFullscreen(GLFWwindow* window) {
	fullscreen = false;
	const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowMonitor(window, NULL, (vidMode->width - windowWidth) / 2, (vidMode->height - windowHeight) / 2, windowWidth, windowHeight, GLFW_DONT_CARE);
}

void toggleFullscreen(GLFWwindow* window) {
	if(fullscreen) {
		disableFullscreen(window);
		return;
	}
	enableFullscreen(window);
}

bool debugMode = true;

int fov = 70;

int speed = 5;

float sensitivity = 0.08f;

int renderDistance = 4;

float lastTime = 0.0f;
float currentTime = 0.0f;
float deltaTime = 0.0f;

void calculateTime() {
	currentTime = (float) glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}

int width(GLFWwindow* window) {
	if(fullscreen) {
		const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		return vidMode->width;
	}
	int width[1];
	glfwGetWindowSize(window, width, NULL);
	return width[0];
}

int height(GLFWwindow* window) {
	if(fullscreen) {
		const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		return vidMode->height;
	}
	int height[1];
	glfwGetWindowSize(window, NULL, height);
	return height[0];
}

Debug::Debug(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGui::StyleColorsDark();
}

void Debug::begin() {
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
}

void Debug::render(std::string title, std::function<void()> render) {
	ImGui::Begin(title.c_str());
	render();
	ImGui::End();
}

void Debug::end() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Debug::~Debug() {
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}

float fpsLastTime = 0.0f;
float fpsCurrentTime = 0.0f;
int frames = 0;
int fps = 0;

void calculateFps() {
	fpsCurrentTime = currentTime;
	float fpsDeltaTime = fpsCurrentTime - fpsLastTime;
	frames++;
	if (fpsDeltaTime < 1.0f) return;
	fps = frames;
	frames = 0;
	fpsLastTime = fpsCurrentTime;
}
