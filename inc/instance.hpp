#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <block.hpp>

extern std::vector<ShaderProgram*> programs;
extern ShaderProgram* chunkProgram;
extern ShaderProgram* blockSelectionProgram;

void loadShaderPrograms();

void unloadShaderPrograms();

extern std::vector<Texture*> textures;
extern Texture* blocksTexture;

void loadTextures();

void unloadTextures();

extern std::vector<BlockModel*> blockModels;
extern BlockModel* airModel;
extern BlockModel* stoneModel;
extern BlockModel* dirtModel;
extern BlockModel* grassBlockModel;
extern BlockModel* glassModel;
extern BlockModel* grassModel;
extern BlockModel* bedrockModel;

void loadBlockModels();

void unloadBlockModels();

extern std::vector<Block*> blocks;
extern Block* air;
extern Block* stone;
extern Block* dirt;
extern Block* grassBlock;
extern Block* glass;
extern Block* grass;
extern Block* bedrock;

void loadBlocks();

void unloadBlocks();

#endif
