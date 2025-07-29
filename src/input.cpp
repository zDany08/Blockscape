#include <input.hpp>
#include <player.hpp>

void onKeyPress(GLFWwindow* window, int key) {
	switch(key) {
		case GLFW_KEY_ESCAPE:
			toggleCursor(window);
			break;
		case GLFW_KEY_F11:
			toggleFullscreen(window);
			break;
	}
}

void onKeyRelease(GLFWwindow* window, int key) {}

void onMouseButtonPress(GLFWwindow* window, Camera* camera, int button) {
	switch(button) {
		case GLFW_MOUSE_BUTTON_1:
			camera->breakBlock();
			break;
		case GLFW_MOUSE_BUTTON_2:
			camera->placeBlock();
			break;
	}
}

void onMouseButtonRelease(GLFWwindow*, Camera* camera, int button) {}

void onCursorMove(GLFWwindow* window, Camera* camera, int mouseX, int mouseY) {
	if(cursorEnabled) return;
	int x = width(window) / 2, y = height(window) / 2;
	camera->rotate(mouseX - x, -(mouseY - y));
	glfwSetCursorPos(window, x, y);
}

void onInput(GLFWwindow* window, Camera* camera) {
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera->move((float) speed, FORWARD);
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera->move((float) speed, LEFT);
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera->move((float) speed, BACK);
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera->move((float) speed, RIGHT);
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera->move((float) speed, UP);
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera->move((float) speed, DOWN);
}

bool cursorEnabled;

void enableCursor(GLFWwindow* window) {
	cursorEnabled = true;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void disableCursor(GLFWwindow* window) {
	cursorEnabled = false;
	glfwSetCursorPos(window, width(window) / 2, height(window) / 2);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void toggleCursor(GLFWwindow* window) {
	if(cursorEnabled) {
		disableCursor(window);
		return;
	}
	enableCursor(window);
}
