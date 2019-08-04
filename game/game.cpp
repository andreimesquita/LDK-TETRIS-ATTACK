#include <ldk/ldk.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <map>

using namespace ldk;

int clamp(int value, int min, int max)
{
	if (value > max) return max;
	if (value < min) return min;
	return value;
};

#include "types.hpp"
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

void initializeLines()
{
	//initialize lines by defining the CoordY of each
	for (int i = 0; i < LINES_ARRAY_LENGTH; i++)
	{
		Line &line = _gameState->lines[i];
		line.CoordY = i;
	}
	
	for (int l = 0; l < LINES_ARRAY_LENGTH; l++)
	{
		Line &line = _gameState->lines[l];
		line.CoordY = l;
		
		for (int c = 0; c < BOARD_COLUMNS; c++)
		{
			Piece &piece = gameplay::getPieceInLine(line, c);
			piece.Type = (PieceType) (rand() % PieceType::PIECE_TYPE_LENGTH);
		}
	}
};

void gameStart(void* memory)
{
	_gameState = (GameState*)memory;
	initializeLines();
	view::initializeView();
	
	unsigned int seed = (unsigned int)std::time(0);
	std::srand(seed);
};

void gameUpdate(float deltaTime)
{
	gameplay::updateLogic(deltaTime);
	view::draw();
};

void gameViewResized(uint32 width, uint32 height)
{
	Rect rect = {0.0f, 0.0f, (float)height, (float)height};
	renderer::setViewPort(rect);
};

void gameStop()
{
	renderer::material_destroy(_gameState->material);
	renderer::spriteBatch_destroy(_gameState->spriteBatch);
	renderer::context_finalize();
};
