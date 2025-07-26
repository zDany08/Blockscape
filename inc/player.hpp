#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <utils.hpp>

enum Direction {

	FORWARD,
	LEFT,
	BACK,
	RIGHT,
	UP,
	DOWN
};

class Camera {
private:
	glm::vec3 position;
public:
	float yaw, pitch;
	glm::vec3 front, up;

	Camera();

	void move(float, Direction);

	void rotate(int, int);

	glm::mat4 projection(GLFWwindow*);

	glm::mat4 view();

	glm::ivec3 worldBlockPosition();
};

#endif
