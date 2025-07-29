#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <rendering.hpp>
#include <physics.hpp>

glm::ivec3 toLocalBlockPosition(glm::ivec3, glm::ivec3, unsigned short);

glm::ivec3 toWorldBlockPosition(glm::ivec3, glm::ivec3, unsigned short);

glm::ivec3 toChunkPosition(glm::ivec3, unsigned short);

struct BlockMesh {
	public:
		std::string id;
		TextureUnit unit;
		glm::vec3 first, second, third, fourth;

		BlockMesh(std::string, TextureUnit, glm::vec3, glm::vec3, glm::vec3, glm::vec3);
};

struct BlockModel {
	public:
		std::string id;
		std::vector<BlockMesh> meshes;
		BoundingBox boundingBox;
		bool translucent;

		BlockModel(std::string, const std::vector<BlockMesh>&, BoundingBox, bool);
};

class Block {
	public:
		std::string id;
		BlockModel* model;
		bool solid;

		Block() = default;

		Block(std::string, BlockModel*, bool);

		virtual void onPlace(glm::ivec3);

		virtual void onBreak(glm::ivec3);
};

class BlockSelection {
	private:
		VertexArrayObject vao;
		BufferObject vbo;
	public:
		glm::vec4 color;
		BoundingBox boundingBox;

		BlockSelection(glm::vec4, glm::ivec3, Block*);

		void render(GLFWwindow*, ShaderProgram*, Camera*);
};

#endif
