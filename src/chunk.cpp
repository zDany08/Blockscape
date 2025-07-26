#include <chunk.hpp>

glm::ivec3 toLocalBlockPosition(glm::ivec3 chunkPosition, glm::ivec3 worldBlockPosition) {
	return toLocalBlockPosition(chunkPosition, worldBlockPosition, chunkSize);
}

glm::ivec3 toWorldBlockPosition(glm::ivec3 chunkPosition, glm::ivec3 localBlockPosition) {
	return toWorldBlockPosition(chunkPosition, localBlockPosition, chunkSize);
}

glm::ivec3 toChunkPosition(glm::ivec3 worldBlockPosition) {
	return toChunkPosition(worldBlockPosition, chunkSize);
}

Block* getBlockAt(glm::ivec3 localBlockPosition, BlockStorage& blocks) {
	return blocks[localBlockPosition.x][localBlockPosition.y][localBlockPosition.z];
}

bool hasBlockAt(glm::ivec3 localBlockPosition, BlockStorage& blocks) {
	return getBlockAt(localBlockPosition, blocks) != nullptr;
}

void placeBlockAt(glm::ivec3 localBlockPosition, Block* block, BlockStorage& blocks) {
	if(!hasBlockAt(localBlockPosition, blocks)) blocks[localBlockPosition.x][localBlockPosition.y][localBlockPosition.z] = block;
}

void breakBlockAt(glm::ivec3 localBlockPosition, BlockStorage& blocks) {
	if(hasBlockAt(localBlockPosition, blocks)) blocks[localBlockPosition.x][localBlockPosition.y][localBlockPosition.z] = nullptr;
}

bool ChunkRenderer::isOpaqueBlockPresentAt(BlockStorage& blocks, glm::ivec3 localBlockPosition) {
	if(localBlockPosition.x < 0 || localBlockPosition.x >= chunkSize) return false;
	if(localBlockPosition.y < 0 || localBlockPosition.y >= chunkSize) return false;
	if(localBlockPosition.z < 0 || localBlockPosition.z >= chunkSize) return false;
	if(!hasBlockAt(localBlockPosition, blocks)) return false;
	Block* block = getBlockAt(localBlockPosition, blocks);
	if(block->model->translucent) return false;
	return true;
}

bool ChunkRenderer::isBoundaryMesh(BlockStorage& blocks, glm::ivec3 blockPosition, Block* block, BlockMesh mesh) {
	float value = 0.0f;
	if(mesh.first.x == mesh.second.x && mesh.second.x == mesh.third.x && mesh.third.x == mesh.fourth.x) {
		float temp = mesh.first.x;
		value = temp > 0 ? isOpaqueBlockPresentAt(blocks, glm::vec3(blockPosition.x + 1, blockPosition.y, blockPosition.z)) ? temp : value : isOpaqueBlockPresentAt(blocks, glm::vec3(blockPosition.x - 1, blockPosition.y, blockPosition.z)) ? temp : value;
	}
	if(mesh.first.y == mesh.second.y && mesh.second.y == mesh.third.y && mesh.third.y == mesh.fourth.y) {
		float temp = mesh.first.y;
		value = temp > 0 ? isOpaqueBlockPresentAt(blocks, glm::vec3(blockPosition.x, blockPosition.y + 1, blockPosition.z)) ? temp : value : isOpaqueBlockPresentAt(blocks, glm::vec3(blockPosition.x, blockPosition.y - 1, blockPosition.z)) ? temp : value;
	}
	if(mesh.first.z == mesh.second.z && mesh.second.z == mesh.third.z && mesh.third.z == mesh.fourth.z) {
		float temp = mesh.first.z;
		value = temp > 0 ? isOpaqueBlockPresentAt(blocks, glm::vec3(blockPosition.x, blockPosition.y, blockPosition.z + 1)) ? temp : value : isOpaqueBlockPresentAt(blocks, glm::vec3(blockPosition.x, blockPosition.y, blockPosition.z - 1)) ? temp : value;
	}
	return value > 0.0f ? value >= 0.5f : value <= -0.5f;
}

void ChunkRenderer::batchMesh(glm::ivec3 chunkPosition, GLsizei& verticesIndex, GLsizei& indicesIndex, GLsizei& index, BlockMesh mesh, glm::ivec3 localBlockPosition) {
	glm::ivec3 position = toWorldBlockPosition(chunkPosition, localBlockPosition);

	vertices[verticesIndex++] = mesh.first.x + position.x;
	vertices[verticesIndex++] = mesh.first.y + position.y;
	vertices[verticesIndex++] = mesh.first.z + position.z;
	vertices[verticesIndex++] = mesh.unit.texX;
	vertices[verticesIndex++] = mesh.unit.texY;

	vertices[verticesIndex++] = mesh.second.x + position.x;
	vertices[verticesIndex++] = mesh.second.y + position.y;
	vertices[verticesIndex++] = mesh.second.z + position.z;
	vertices[verticesIndex++] = mesh.unit.texX + mesh.unit.texWidth;
	vertices[verticesIndex++] = mesh.unit.texY;

	vertices[verticesIndex++] = mesh.third.x + position.x;
	vertices[verticesIndex++] = mesh.third.y + position.y;
	vertices[verticesIndex++] = mesh.third.z + position.z;
	vertices[verticesIndex++] = mesh.unit.texX + mesh.unit.texWidth;
	vertices[verticesIndex++] = mesh.unit.texY + mesh.unit.texHeight;

	vertices[verticesIndex++] = mesh.fourth.x + position.x;
	vertices[verticesIndex++] = mesh.fourth.y + position.y;
	vertices[verticesIndex++] = mesh.fourth.z + position.z;
	vertices[verticesIndex++] = mesh.unit.texX;
	vertices[verticesIndex++] = mesh.unit.texY + mesh.unit.texHeight;

	indices[indicesIndex++] = index;
	indices[indicesIndex++] = index + 1;
	indices[indicesIndex++] = index + 2;
	indices[indicesIndex++] = index + 2;
	indices[indicesIndex++] = index + 3;
	indices[indicesIndex++] = index;
	index += 4;
}

ChunkRenderer::ChunkRenderer() : vao(VertexArrayObject()), vbo(BufferObject(GL_ARRAY_BUFFER)), ebo(BufferObject(GL_ELEMENT_ARRAY_BUFFER)), vertices(nullptr), indices(nullptr), size(0) {
	vao.bind();
	vbo.bind();
	vbo.attrib(0, 3, GL_FLOAT, 5 * sizeof(GLfloat), (GLvoid*) 0);
	vbo.attrib(1, 2, GL_FLOAT, 5 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
	vbo.unbind();
	vao.unbind();
}

void ChunkRenderer::batch(glm::ivec3 chunkPosition, BlockStorage& blocks) {
	GLsizei verticesSize = 0, indicesSize = 0, verticesIndex = 0, indicesIndex = 0;
	GLsizei index = 0;
	for(int x = 0; x < chunkSize; x++) for (int y = 0; y < chunkSize; y++) for (int z = 0; z < chunkSize; z++) {
		glm::ivec3 position = glm::ivec3(x, y, z);
		if(!hasBlockAt(position, blocks)) continue;
		Block* block = getBlockAt(position, blocks);
		for(BlockMesh& mesh : block->model->meshes) {
			if(!isBoundaryMesh(blocks, glm::ivec3(x, y, z), block, mesh)) {
				verticesSize++;
				indicesSize++;
			}
		}
	}
	verticesSize *= 20 * sizeof(GLfloat);
	indicesSize *= 6 * sizeof(GLfloat);
	vertices = new GLfloat[verticesSize];
	indices = new GLint[indicesSize];
	for(int x = 0; x < chunkSize; x++) for (int y = 0; y < chunkSize; y++) for (int z = 0; z < chunkSize; z++) {
		glm::ivec3 position = glm::ivec3(x, y, z);
		if(!hasBlockAt(position, blocks)) continue;
		Block* block = getBlockAt(position, blocks);
		for(BlockMesh& mesh : block->model->meshes) if (!isBoundaryMesh(blocks, glm::ivec3(x, y, z), block, mesh)) batchMesh(chunkPosition, verticesIndex, indicesIndex, index, mesh, glm::ivec3(x, y, z));
	}
	vbo.bind();
	vbo.data(verticesSize, vertices, GL_STATIC_DRAW);
	vbo.unbind();
	ebo.bind();
	ebo.data(indicesSize, indices, GL_STATIC_DRAW);
	ebo.unbind();
	size = indicesSize;
}

void ChunkRenderer::render(GLFWwindow* window, Camera* camera) {
	if(size == 0) return;
	chunkProgram->bind();
	chunkProgram->uniform(camera->projection(window), "uProjection");
	chunkProgram->uniform(camera->view(), "uView");
	chunkProgram->uniform(0, "uTex");
	blocksTexture->bind();
	vao.bind();
	ebo.bind();
	ebo.drawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT);
	ebo.unbind();
	vao.unbind();
	blocksTexture->unbind();
	chunkProgram->unbind();
}

ChunkRenderer::~ChunkRenderer() {
	delete[] vertices;
	delete[] indices;
}

Chunk::Chunk(glm::ivec3 position_) : renderer(ChunkRenderer()), updateNeeded(false), position(position_), blocks(BlockStorage()) {}

void Chunk::render(GLFWwindow* window, Camera* camera) {
	if(updateNeeded) {
		renderer.batch(position, blocks);
		updateNeeded = false;
	}
	renderer.render(window, camera);
}

Block* Chunk::getBlockAt(glm::ivec3 localBlockPosition) {
	return ::getBlockAt(localBlockPosition, blocks);
}

bool Chunk::hasBlockAt(glm::ivec3 localBlockPosition) {
	return ::hasBlockAt(localBlockPosition, blocks);
}

void Chunk::placeBlockAt(glm::ivec3 localBlockPosition, Block* block) {
	::placeBlockAt(localBlockPosition, block, blocks);
	updateNeeded = true;
}

void Chunk::breakBlockAt(glm::vec3 localBlockPosition) {
	::breakBlockAt(localBlockPosition, blocks);
	updateNeeded = true;
}
