#include <instance.hpp>

std::vector<ShaderProgram*> programs;
ShaderProgram* chunkProgram;
ShaderProgram* blockSelectionProgram;

void loadShaderPrograms() {
	programs.push_back(chunkProgram = new ShaderProgram());
	chunkProgram->attachShader(Shader(Resource("shaders/chunk.vert"), GL_VERTEX_SHADER));
	chunkProgram->attachShader(Shader(Resource("shaders/chunk.frag"), GL_FRAGMENT_SHADER));
	chunkProgram->link();
	programs.push_back(blockSelectionProgram = new ShaderProgram());
	blockSelectionProgram->attachShader(Shader(Resource("shaders/block_selection.vert"), GL_VERTEX_SHADER));
	blockSelectionProgram->attachShader(Shader(Resource("shaders/block_selection.frag"), GL_FRAGMENT_SHADER));
	blockSelectionProgram->link();
}

void unloadShaderPrograms() {
	for(ShaderProgram* program : programs) delete program;
}

std::vector<Texture*> textures;
Texture* blocksTexture;

void loadTextures() {
	textures.push_back(blocksTexture = new Texture(Resource("textures/blocks.png")));
}

void unloadTextures() {
	for(Texture* texture : textures) delete texture;
}

std::vector<BlockModel*> blockModels;
BlockModel* airModel;
BlockModel* stoneModel;
BlockModel* dirtModel;
BlockModel* grassBlockModel;
BlockModel* grassModel;
BlockModel* glassModel;
BlockModel* bedrockModel;

void loadBlockModels() {
	blockModels.push_back(airModel = new BlockModel("air", {}, BoundingBox(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)), false));
	blockModels.push_back(stoneModel = new BlockModel("stone", {
		BlockMesh("right", blocksTexture->get(0, 0, 16, 16), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f)),
		BlockMesh("left", blocksTexture->get(0, 0, 16, 16), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f)),
		BlockMesh("top", blocksTexture->get(0, 0, 16, 16), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f)),
		BlockMesh("bottom", blocksTexture->get(0, 0, 16, 16), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f)),
		BlockMesh("front", blocksTexture->get(0, 0, 16, 16), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f)),
		BlockMesh("back", blocksTexture->get(0, 0, 16, 16), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f))
	}, BoundingBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f)), false));
	blockModels.push_back(dirtModel = new BlockModel("dirt", {
		BlockMesh("right", blocksTexture->get(16, 0, 16, 16), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f)),
		BlockMesh("left", blocksTexture->get(16, 0, 16, 16), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f)),
		BlockMesh("top", blocksTexture->get(16, 0, 16, 16), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f)),
		BlockMesh("bottom", blocksTexture->get(16, 0, 16, 16), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f)),
		BlockMesh("front", blocksTexture->get(16, 0, 16, 16), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f)),
		BlockMesh("back", blocksTexture->get(16, 0, 16, 16), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f))
	}, BoundingBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f)), false));
	blockModels.push_back(grassBlockModel = new BlockModel("grass_block", {
		BlockMesh("right", blocksTexture->get(32, 0, 16, 16), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f)),
		BlockMesh("left", blocksTexture->get(32, 0, 16, 16), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f)),
		BlockMesh("top", blocksTexture->get(48, 0, 16, 16), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f)),
		BlockMesh("bottom", blocksTexture->get(16, 0, 16, 16), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f)),
		BlockMesh("front", blocksTexture->get(32, 0, 16, 16), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f)),
		BlockMesh("back", blocksTexture->get(32, 0, 16, 16), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f))
	}, BoundingBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f)), false));
	blockModels.push_back(grassModel = new BlockModel("grass", {
		BlockMesh("first", blocksTexture->get(64, 0, 16, 16), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f)),
		BlockMesh("second", blocksTexture->get(64, 0, 16, 16), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, 0.5f))
	}, BoundingBox(glm::vec3(-0.2f, -0.5f, -0.2f), glm::vec3(0.2f, 0.2f, 0.2f)), true));
	blockModels.push_back(glassModel = new BlockModel("glass", {
		BlockMesh("right", blocksTexture->get(80, 0, 16, 16), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f)),
		BlockMesh("left", blocksTexture->get(80, 0, 16, 16), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f)),
		BlockMesh("top", blocksTexture->get(80, 0, 16, 16), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f)),
		BlockMesh("bottom", blocksTexture->get(80, 0, 16, 16), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f)),
		BlockMesh("front", blocksTexture->get(80, 0, 16, 16), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f)),
		BlockMesh("back", blocksTexture->get(80, 0, 16, 16), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f))
	}, BoundingBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f)), true));
	blockModels.push_back(bedrockModel = new BlockModel("bedrock", {
		BlockMesh("right", blocksTexture->get(96, 0, 16, 16), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f)),
		BlockMesh("left", blocksTexture->get(96, 0, 16, 16), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f)),
		BlockMesh("top", blocksTexture->get(96, 0, 16, 16), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f)),
		BlockMesh("bottom", blocksTexture->get(96, 0, 16, 16), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f)),
		BlockMesh("front", blocksTexture->get(96, 0, 16, 16), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f)),
		BlockMesh("back", blocksTexture->get(96, 0, 16, 16), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f))
	}, BoundingBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f)), false));
}

void unloadBlockModels() {
	for(BlockModel* model : blockModels) delete model;
}

std::vector<Block*> blocks;
Block* air;
Block* stone;
Block* dirt;
Block* grassBlock;
Block* grass;
Block* glass;
Block* bedrock;

void loadBlocks() {
	blocks.push_back(air = new Block("air", airModel, false));
	blocks.push_back(stone = new Block("stone", stoneModel, true));
	blocks.push_back(dirt = new Block("dirt", dirtModel, true));
	blocks.push_back(grassBlock = new Block("grass_block", grassBlockModel, true));
	blocks.push_back(grass = new Block("grass", grassModel, false));
	blocks.push_back(glass = new Block("glass", glassModel, true));
	blocks.push_back(bedrock = new Block("bedrock", bedrockModel, true));
}

void unloadBlocks() {
	for(Block* block : blocks) delete block;
}
