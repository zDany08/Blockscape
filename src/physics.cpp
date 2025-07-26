#include <physics.hpp>

BoundingBoxFace::BoundingBoxFace(glm::vec3 first_, glm::vec3 second_, glm::vec3 third_, glm::vec3 fourth_) : first(first_), second(second_), third(third_), fourth(fourth_) {}

BoundingBox::BoundingBox(glm::vec3 begin_, glm::vec3 end_) {
	glm::vec3 rightBottomBack = begin_ + glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 leftBottomBack = begin_;
	glm::vec3 rightTopBack = begin_ + glm::vec3(1.0f, 1.0f, 0.0f);
	glm::vec3 leftTopBack = begin_ + glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 rightBottomFront = begin_ + glm::vec3(1.0f, 0.0f, 1.0f);
	glm::vec3 leftBottomFront = begin_ + glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 rightTopFront = end_;
	glm::vec3 leftTopFront = begin_ + glm::vec3(0.0f, 1.0f, 1.0f);
	right = BoundingBoxFace(rightBottomBack, rightBottomFront, rightTopFront, rightTopBack);
	left = BoundingBoxFace(leftBottomBack, leftBottomFront, leftTopFront, leftTopBack);
	top = BoundingBoxFace(leftTopFront, rightTopFront, rightTopBack, leftTopBack);
	bottom = BoundingBoxFace(leftBottomFront, rightBottomFront, rightBottomBack, leftBottomBack);
	front = BoundingBoxFace(leftBottomFront, rightBottomFront, rightTopFront, leftTopFront);
	back = BoundingBoxFace(leftBottomBack, rightBottomBack, rightTopBack, leftTopBack);
}
