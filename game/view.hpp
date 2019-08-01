static const uint32 WINDOW_WIDTH = 600;
static const uint32 WINDOW_HEIGHT = 800;
static const float ASPECT_RATIO = 1.0f;
static const uint32 PIECE_SIZE = 16;
static const uint32 SCREEN_PIECE_SIZE = 32;

namespace view
{
	//**********************
	//* Utils
	//**********************
	Vec2 screenPositionToCoordinate(Vec2 screenPosition)
	{
		//TODO(andrei) 
		//TODO(andrei) remember to use the animation's offset during calculation
		return {0,0};
	};
	
	//**********************
	//* Initialization
	//**********************
	void initializePieceSprites()
	{
		for (int i = 1; i < PIECE_TYPE_LENGTH; i++)
		{
			renderer::makeSprite(&_gameState->sprites[i], _gameState->material,
								(i*19), 0,
								PIECE_SIZE, PIECE_SIZE);
		}
	};

	void initializeBoardSprites()
	{
		Vec4 clearColor = Vec4{0.0f, 0.0f, 0.0f, 0.0f};
		renderer::context_initialize(255, clearColor, 0);
		_gameState->material = loadMaterial("./assets/piece.mat");
		_gameState->projMatrix.orthographic(0, 600, 0, 800, -10, 10);
		_gameState->spriteBatch = renderer::spriteBatch_create(1024);
		initializePieceSprites();
	};
	
	//**********************
	//* Rendering
	//**********************
	inline renderer::Sprite* getSpriteByPieceType(PieceType pieceType)
	{
		return &(_gameState->sprites[(uint32)pieceType]);
	};
	
	inline void drawAllPieces()
	{
		return;
		//TODO(andrei) double check with Freitas why this is crashing the game
		renderer::spriteBatch_draw(_gameState->spriteBatch,
										   &(_gameState->sprites[0]),
										   (SCREEN_PIECE_SIZE * 0), (SCREEN_PIECE_SIZE * 1),
										   SCREEN_PIECE_SIZE, SCREEN_PIECE_SIZE);
		renderer::spriteBatch_draw(_gameState->spriteBatch,
										   &(_gameState->sprites[0]),
										   (SCREEN_PIECE_SIZE * 1), (SCREEN_PIECE_SIZE * 1),
										   SCREEN_PIECE_SIZE, SCREEN_PIECE_SIZE);
		renderer::spriteBatch_draw(_gameState->spriteBatch,
										   &(_gameState->sprites[0]),
										   (SCREEN_PIECE_SIZE * 2), (SCREEN_PIECE_SIZE * 1),
										   SCREEN_PIECE_SIZE, SCREEN_PIECE_SIZE);
										   
		for (int l = 0; l < LINES_ARRAY_LENGTH; l++)
		{
			Line &line = _gameState->lines[l];
			
			for (int c = 0; c < BOARD_COLUMNS; c++)
			{
				Piece &piece = gameplay::getPieceInLine(line, c);
				
				if (gameplay::isPieceEmpty(piece)) continue;
				
				renderer::spriteBatch_draw(_gameState->spriteBatch,
										   getSpriteByPieceType(piece.Type),
										   (SCREEN_PIECE_SIZE * c), (SCREEN_PIECE_SIZE * l),
										   SCREEN_PIECE_SIZE, SCREEN_PIECE_SIZE);
			}
		}
	};
	
	void draw()
	{
		renderer::clearBuffers(renderer::Context::COLOR_BUFFER | renderer::Context::DEPTH_BUFFER);
		renderer::beginFrame(_gameState->projMatrix);
		renderer::spriteBatch_begin(_gameState->spriteBatch);
		drawAllPieces();
		renderer::spriteBatch_end(_gameState->spriteBatch);
		renderer::endFrame();
	};
};
