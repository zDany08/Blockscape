#include <input.hpp>
#include <chunk.hpp>
#include <renderer.hpp>

GLFWwindow* window;
Camera* camera;
World* world;
Debug* debug;

void onError(int errorCode, const char* description) {
	std::cerr << "Error " << errorCode << ": " << description << std::endl;
}

void onResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void onFocus(GLFWwindow* window, int focused_) {
	focused = focused_;
}

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch(action) {
		case GLFW_PRESS:
			onKeyPress(window, key);
			break;
		case GLFW_RELEASE:
			onKeyRelease(window, key);
			break;
	}
}

void onMouseButton(GLFWwindow* window, int button, int action, int mods) {
	switch(action) {
		case GLFW_PRESS:
			onMouseButtonPress(window, camera, button);
			break;
		case GLFW_RELEASE:
			onMouseButtonRelease(window, camera, button);
			break;
	}
}

void onCursorPos(GLFWwindow* window, double mouseX, double mouseY) {
	onCursorMove(window, camera, (int) mouseX, (int) mouseY);
}

void initCallbacks() {
	glfwSetFramebufferSizeCallback(window, onResize);
	glfwSetWindowFocusCallback(window, onFocus);
	glfwSetKeyCallback(window, onKey);
	glfwSetMouseButtonCallback(window, onMouseButton);
	glfwSetCursorPosCallback(window, onCursorPos);
}

void init() {
	if(!gladLoadGL()) {
		std::cerr << "Failed to initialize OpenGL" << std::endl;
		glfwTerminate();
		std::exit(1);
	}
	loadShaderPrograms();
	loadTextures();
	loadBlockModels();
	loadBlocks();
	camera = new Camera();
	world = new World();
	debug = new Debug(window);
}

void start() {
	std::cout << "Starting..." << std::endl;
	glfwSetErrorCallback(onError);
	if(!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		std::exit(1);
	}
	window = glfwCreateWindow(windowWidth, windowHeight, "Blockscape", NULL, NULL);
	if(!window) {
		std::cerr << "Failed to create the GLFW window" << std::endl;
		glfwTerminate();
		std::exit(1);
	}
	initCallbacks();
	disableFullscreen(window);
	disableCursor(window);
	glfwMakeContextCurrent(window);
	init();
}

void loop() {
	calculateTime();
	calculateFps();
	calculateDayTime();
	onInput(window, camera);
	render(window, world, camera, debug);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void stop() {
	std::cout << "Stopping..." << std::endl;
	delete debug;
	delete world;
	delete camera;
	unloadBlocks();
	unloadBlockModels();
	unloadTextures();
	unloadShaderPrograms();
	glfwDestroyWindow(window);
	glfwTerminate();
}

int main(int argc, char** argv) {
	start();
	while(!glfwWindowShouldClose(window)) loop();
	stop();
}
