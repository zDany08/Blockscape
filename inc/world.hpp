#ifndef WORLD_HPP
#define WORLD_HPP

#include <chunk.hpp>
#include <mutex>

constexpr unsigned short maxWorldSize = 128;

using ChunkStorage = std::array<std::array<std::array<Chunk*, maxWorldSize>, maxWorldSize>, maxWorldSize>;

class World {
public:
	ChunkStorage chunks;
	std::mutex mtx;

	World();

	void generateChunkAt(glm::ivec3);

	void render(GLFWwindow*, Camera*);

	Chunk* getChunkAt(glm::ivec3);

	bool hasChunkAt(glm::ivec3);

	~World();
};

#endif
