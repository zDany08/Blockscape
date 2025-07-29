#ifndef PLAYER_HPP
#define PLAYER_HPP

enum Direction {

	FORWARD,
	LEFT,
	BACK,
	RIGHT,
	UP,
	DOWN
};

class Camera {
	public:
		float yaw, pitch;
		glm::vec3 position, front, up;

		Camera();

		void move(float, Direction);

		void rotate(int, int);

		void placeBlock();

		void breakBlock();

		glm::mat4 projection(GLFWwindow*);

		glm::mat4 view();

		glm::ivec3 worldBlockPosition();
};

#endif
