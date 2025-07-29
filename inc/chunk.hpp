#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <instance.hpp>

constexpr unsigned short chunkSize = 16;

using BlockStorage = std::array<std::array<std::array<Block*, chunkSize>, chunkSize>, chunkSize>;

glm::ivec3 toLocalBlockPosition(glm::ivec3, glm::ivec3);

glm::ivec3 toWorldBlockPosition(glm::ivec3, glm::ivec3);

glm::ivec3 toChunkPosition(glm::ivec3);

Block* getBlockAt(glm::ivec3, BlockStorage&);

bool hasBlockAt(glm::ivec3, BlockStorage&);

void placeBlockAt(glm::ivec3, Block*, BlockStorage&);

void breakBlockAt(glm::ivec3, BlockStorage&);

class ChunkRenderer {
	private:
		VertexArrayObject vao;
		BufferObject vbo, ebo;
		GLfloat* vertices;
		GLint* indices;
		GLsizei size;

		bool isOpaqueBlockPresentAt(BlockStorage&, glm::ivec3);

		bool isBoundaryMesh(BlockStorage&, glm::ivec3, Block*, BlockMesh);

		void batchMesh(glm::ivec3, GLsizei&, GLsizei&, GLsizei&, BlockMesh, glm::ivec3);
	public:
		ChunkRenderer();

		void batch(glm::ivec3, BlockStorage&);

		void render(GLFWwindow*, Camera*);

		~ChunkRenderer();
};

struct Chunk {
	private:
		ChunkRenderer renderer;
		bool updateNeeded;
	public:
		glm::ivec3 position;
		BlockStorage blocks;

		Chunk() = default;

		Chunk(glm::ivec3);

		void render(GLFWwindow*, Camera*);

		Block* getBlockAt(glm::ivec3);

		bool hasBlockAt(glm::ivec3);

		void placeBlockAt(glm::ivec3, Block*);

		void breakBlockAt(glm::vec3);
};

#endif
