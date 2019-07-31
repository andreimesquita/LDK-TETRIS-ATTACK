#include <ldk/ldk.h>

using namespace ldk;

#include "types.h"
#include "gameplay.hpp"
#include "view.hpp"

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
	view::initializeBoardSprites();
};

void gameUpdate(float deltaTime)
{
	view::draw();
};

void gameStop()
{
	renderer::material_destroy(_gameState->material);
	renderer::spriteBatch_destroy(_gameState->spriteBatch);
	renderer::context_finalize();
};
