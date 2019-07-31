#include <ldk/ldk.h>

using namespace ldk;

#include "types.h"

static struct GameState
{
	renderer::SpriteBatch* spriteBatch;
	Mat4 modelMatrix;
	Mat4 projMatrix;
	HMaterial material;
	renderer::Sprite sprite;
} *_gameState;

#include "view.h"

void initializePieces()
{
	//TODO
};

void initializeBoard()
{
	//TODO
};

LDKGameSettings gameInit()
{
	LDKGameSettings settings;
	settings.displayWidth = WINDOW_WIDTH;
	settings.displayHeight = WINDOW_HEIGHT;
	settings.aspect = ASPECT_RATIO;
	settings.fullScreen = false;
	settings.name = "LDK Tetris Attack";
	settings.preallocMemorySize = sizeof(GameState);
	return settings;
};

void gameStart(void* memory)
{
	_gameState = (GameState*)memory;

	Vec4 clearColor = Vec4{0.0f, 0.0f, 0.0f, 0.0f};
	renderer::context_initialize(255, clearColor, 0);
	  
	_gameState->material = loadMaterial("./assets/piece.mat");
	 
	_gameState->projMatrix.orthographic(0, 600, 0, 800, -10, 10);
	renderer::material_setMatrix4(_gameState->material, "mprojection", &_gameState->projMatrix);
	// model
	_gameState->modelMatrix.identity();
	_gameState->modelMatrix.translate(Vec3{0, 0, -2});
	renderer::material_setMatrix4(_gameState->material, "mmodel", &_gameState->modelMatrix);

	renderer::makeSprite(&_gameState->sprite, _gameState->material, 0, 0, 16, 16);

	// Initialize the sprite batch
	_gameState->spriteBatch = renderer::spriteBatch_create(16); 
};

void gameUpdate(float deltaTime)
{
	//TODO
	draw();
};

void gameStop()
{
	renderer::material_destroy(_gameState->material);
	renderer::spriteBatch_destroy(_gameState->spriteBatch);
	renderer::context_finalize();
};
