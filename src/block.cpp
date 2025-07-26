#include <block.hpp>

glm::ivec3 toLocalBlockPosition(glm::ivec3 chunkPosition, glm::ivec3 worldBlockPosition, unsigned short chunkSize) {
	return worldBlockPosition - (chunkPosition * glm::ivec3(chunkSize));
}

glm::ivec3 toWorldBlockPosition(glm::ivec3 chunkPosition, glm::ivec3 localBlockPosition, unsigned short chunkSize) {
	return localBlockPosition + (chunkPosition * glm::ivec3(chunkSize));
}

glm::ivec3 toChunkPosition(glm::ivec3 worldBlockPosition, unsigned short chunkSize) {
	return glm::ivec3(worldBlockPosition.x / chunkSize, worldBlockPosition.y / chunkSize, worldBlockPosition.z / chunkSize);
}

BlockMesh::BlockMesh(std::string id_, TextureUnit unit_, glm::vec3 first_, glm::vec3 second_, glm::vec3 third_, glm::vec3 fourth_) : id(id_), unit(unit_), first(first_), second(second_), third(third_), fourth(fourth_) {}

BlockModel::BlockModel(std::string id_, const std::vector<BlockMesh>& meshes_, BoundingBox boundingBox_, bool translucent_) : id(id_), meshes(meshes_), boundingBox(boundingBox_), translucent(translucent_) {}

Block::Block(std::string id_, BlockModel* model_, bool solid_) : id(id_), model(model_), solid(solid_) {}

void Block::onPlace(glm::ivec3 position) {}

void Block::onBreak(glm::ivec3 position) {}

BlockSelection::BlockSelection(glm::vec4 color_, glm::ivec3 position_, Block* block_) : vao(VertexArrayObject()), vbo(BufferObject(GL_ARRAY_BUFFER)), color(color_), boundingBox(block_->model->boundingBox) {
	GLfloat vertices[100] = {
		boundingBox.back.first.x + position_.x, boundingBox.back.first.y + position_.y, boundingBox.back.first.z + position_.z,
		boundingBox.back.second.x + position_.x, boundingBox.back.second.y + position_.y, boundingBox.back.second.z + position_.z,

		boundingBox.back.second.x + position_.x, boundingBox.back.second.y + position_.y, boundingBox.back.second.z + position_.z,
		boundingBox.back.third.x + position_.x, boundingBox.back.third.y + position_.y, boundingBox.back.third.z + position_.z,

		boundingBox.back.third.x + position_.x, boundingBox.back.third.y + position_.y, boundingBox.back.third.z + position_.z,
		boundingBox.back.fourth.x + position_.x, boundingBox.back.fourth.y + position_.y, boundingBox.back.fourth.z + position_.z,

		boundingBox.back.fourth.x + position_.x, boundingBox.back.fourth.y + position_.y, boundingBox.back.fourth.z + position_.z,
		boundingBox.back.first.x + position_.x, boundingBox.back.first.y + position_.y, boundingBox.back.first.z + position_.z,

		boundingBox.front.first.x + position_.x, boundingBox.front.first.y + position_.y, boundingBox.front.first.z + position_.z,
		boundingBox.front.second.x + position_.x, boundingBox.front.second.y + position_.y, boundingBox.front.second.z + position_.z,

		boundingBox.front.second.x + position_.x, boundingBox.front.second.y + position_.y, boundingBox.front.second.z + position_.z,
		boundingBox.front.third.x + position_.x, boundingBox.front.third.y + position_.y, boundingBox.front.third.z + position_.z,

		boundingBox.front.third.x + position_.x, boundingBox.front.third.y + position_.y, boundingBox.front.third.z + position_.z,
		boundingBox.front.fourth.x + position_.x, boundingBox.front.fourth.y + position_.y, boundingBox.front.fourth.z + position_.z,

		boundingBox.front.fourth.x + position_.x, boundingBox.front.fourth.y + position_.y, boundingBox.front.fourth.z + position_.z,
		boundingBox.front.first.x + position_.x, boundingBox.front.first.y + position_.y, boundingBox.front.first.z + position_.z,

		boundingBox.back.first.x + position_.x, boundingBox.back.first.y + position_.y, boundingBox.back.first.z + position_.z,
		boundingBox.front.first.x + position_.x, boundingBox.front.first.y + position_.y, boundingBox.front.first.z + position_.z,

		boundingBox.back.second.x + position_.x, boundingBox.back.second.y + position_.y, boundingBox.back.second.z + position_.z,
		boundingBox.front.second.x + position_.x, boundingBox.front.second.y + position_.y, boundingBox.front.second.z + position_.z,

		boundingBox.back.third.x + position_.x, boundingBox.back.third.y + position_.y, boundingBox.back.third.z + position_.z,
		boundingBox.front.third.x + position_.x, boundingBox.front.third.y + position_.y, boundingBox.front.third.z + position_.z,

		boundingBox.back.fourth.x + position_.x, boundingBox.back.fourth.y + position_.y, boundingBox.back.fourth.z + position_.z,
		boundingBox.front.fourth.x + position_.x, boundingBox.front.fourth.y + position_.y, boundingBox.front.fourth.z + position_.z
	};
	vao.bind();
	vbo.bind();
	vbo.data(sizeof(vertices), vertices, GL_STATIC_DRAW);
	vbo.attrib(0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (GLvoid*) 0);
	vbo.unbind();
	vao.unbind();
}

void BlockSelection::render(GLFWwindow* window, ShaderProgram* program, Camera* camera) {
	program->bind();
	program->uniform(color, "uColor");
	program->uniform(camera->projection(window), "uProjection");
	program->uniform(camera->view(), "uView");
	vao.bind();
	vbo.bind();
	vbo.drawArrays(GL_LINES, 0, 24);
	vbo.unbind();
	vao.unbind();
	program->unbind();
}
