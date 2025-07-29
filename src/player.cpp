#include <input.hpp>
#include <player.hpp>

Camera::Camera() : position(glm::vec3(0.0f)), yaw(-90.0f), pitch(0.0f), front(glm::vec3(0.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)) {}

void Camera::move(float speed, Direction direction) {
	float velocity = speed * deltaTime;
	glm::vec3 forward = glm::vec3(front.x, 0.0f, front.z);
	glm::vec3 right = glm::cross(forward, up);
	switch(direction) {
		case RIGHT:
			position += right * velocity;
			break;
		case LEFT:
			position -= right * velocity;
			break;
		case UP:
			position += up * velocity;
			break;
		case DOWN:
			position -= up * velocity;
			break;
		case FORWARD:
			position += forward * velocity;
			break;
		case BACK:
			position -= forward * velocity;
			break;
	}
}

void Camera::rotate(int xOffset, int yOffset) {
	yaw += (float) xOffset * sensitivity;
	pitch += (float) yOffset * sensitivity;
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;
	float radYaw = glm::radians(yaw);
	float radPitch = glm::radians(pitch);
	front.x = glm::cos(radYaw) * glm::cos(radPitch);
	front.y = glm::sin(radPitch);
	front.z = glm::sin(radYaw) * glm::cos(radPitch);
	front = glm::normalize(front);
}

void Camera::placeBlock() {
	info("Place Break");
}

void Camera::breakBlock() {
	info("Break Block");
}

glm::mat4 Camera::projection(GLFWwindow* window) {
	float aspectRatio = (float) width(window) / height(window);
	return glm::perspective(glm::radians((float) fov), aspectRatio, 0.1f, 1000.0f);
}

glm::mat4 Camera::view() {
	return glm::lookAt(position, position + front, up);
}

glm::ivec3 Camera::worldBlockPosition() {
	return glm::ivec3((int) position.x, (int) position.y, (int) position.z);
}
