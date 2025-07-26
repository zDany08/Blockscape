#include <world.hpp>

World::World() : chunks(ChunkStorage()) {}

void World::generateChunkAt(glm::ivec3 position) {
	mtx.lock();
	chunks[position.x][position.y][position.z] = new Chunk(position);
	Chunk* chunk = getChunkAt(position);
	for(int x = 0; x < chunkSize; x++) for (int y = 0; y < chunkSize; y++) for (int z = 0; z < chunkSize; z++) {
		Block* target = stone;
		if(position.y > 3) target = air;
		if(position.y == 3) {
			target = dirt;
			if(y == chunkSize - 1) target = grassBlock;
		}
		chunk->placeBlockAt(glm::ivec3(x, y, z), target);
	}
	mtx.unlock();
}

void World::render(GLFWwindow* window, Camera* camera) {
	glm::ivec3 chunkPosition = toChunkPosition(camera->worldBlockPosition());
	for(int x = chunkPosition.x - renderDistance; x < chunkPosition.x + renderDistance; x++) {
		if(x < 0 || x >= maxWorldSize) continue;
		for(int y = chunkPosition.y - renderDistance; y < chunkPosition.y + renderDistance; y++) {
			if (y < 0 || y >= maxWorldSize) continue;
			for(int z = chunkPosition.z - renderDistance; z < chunkPosition.z + renderDistance; z++) {
				if (z < 0 || z >= maxWorldSize) continue;
				glm::ivec3 position = glm::ivec3(x, y, z);
				if(!hasChunkAt(position)) generateChunkAt(position);
				getChunkAt(position)->render(window, camera);
			}
		}
	}
}

Chunk* World::getChunkAt(glm::ivec3 position) {
	return chunks[position.x][position.y][position.z];
}

bool World::hasChunkAt(glm::ivec3 position) {
	return getChunkAt(position) != nullptr;
}

World::~World() {
	for(int x = 0; x < maxWorldSize; x++) for(int y = 0; y < maxWorldSize; y++) for(int z = 0; z < maxWorldSize; z++) if(hasChunkAt(glm::ivec3(x, y, z))) delete getChunkAt(glm::ivec3(x, y, z));
}
