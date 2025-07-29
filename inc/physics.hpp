#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <utils.hpp>

struct BoundingBoxFace {
	public:
		glm::vec3 first, second, third, fourth;

		BoundingBoxFace() = default;

		BoundingBoxFace(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
};

struct BoundingBox {
	public:
		BoundingBoxFace right, left, top, bottom, front, back;

		BoundingBox(glm::vec3, glm::vec3);
};

#endif
