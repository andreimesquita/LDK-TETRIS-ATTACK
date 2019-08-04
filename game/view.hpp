static const uint32 WINDOW_WIDTH = 800;
static const uint32 WINDOW_HEIGHT = 800;
static const float ASPECT_RATIO = 1.0f;
static const uint32 PIECE_SIZE = 16;
static const uint32 SCREEN_PIECE_SIZE = 64;
static const uint32 CURSOR_WIDTH = (SCREEN_PIECE_SIZE * 2.1f);
static const uint32 CURSOR_HEIGHT = (SCREEN_PIECE_SIZE * 1.1f);

namespace view
{
	//**********************
	//* Utils
	//**********************
	inline Vec2Int coordinateToScreenPosition(int x, int y)
	{
		return Vec2Int(x * SCREEN_PIECE_SIZE, y * SCREEN_PIECE_SIZE);
	};
	
	//**********************
	//* Initialization
	//**********************	
	void initializePieceSprites()
	{
		for (int i = 0; i < PIECE_TYPE_LENGTH; i++)
		{
			renderer::makeSprite(&_gameState->sprites[i], _gameState->material,
								(i*19), 0,
								PIECE_SIZE, PIECE_SIZE);
		}
	};
	
	void initializeCursor()
	{
		_gameState->cursor.xCoord = 2;
		_gameState->cursor.yCoord = 5;
		
		renderer::makeSprite(&_gameState->cursor.sprite, _gameState->material,
								133, 0,
								32, 16);
	};
	
	void initializeView()
	{
		Vec4 clearColor = Vec4{0.0f, 0.0f, 0.0f, 0.0f};
		renderer::context_initialize(255, clearColor, 0);
		_gameState->material = loadMaterial("./assets/piece.mat");
		_gameState->projMatrix.orthographic(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -10, 10);
		_gameState->spriteBatch = renderer::spriteBatch_create(256);
		
		initializeCursor();
		initializePieceSprites();
	};
	
	//**********************
	//* Rendering
	//**********************
	inline renderer::Sprite* getSpriteByPieceType(PieceType pieceType)
	{
		return &(_gameState->sprites[(uint32)pieceType]);
	};
	
	inline void drawBoardPieces()
	{
		const uint32 centerXPosition = WINDOW_WIDTH * 0.5f;
		
		for (int l = 0; l < BOARD_LINES; l++)
		{
			Line &line = _gameState->lines[l];
			
			for (int c = 0; c < BOARD_COLUMNS; c++)
			{
				Piece &piece = gameplay::getPieceInLine(line, c);
				
				if (gameplay::isPieceEmpty(piece)) continue;
				
				int xPosition = (SCREEN_PIECE_SIZE * c);
				int yPosition = (SCREEN_PIECE_SIZE * line.CoordY);
				
				renderer::spriteBatch_draw(_gameState->spriteBatch,
										   getSpriteByPieceType(piece.Type),
										   xPosition, yPosition,
										   SCREEN_PIECE_SIZE, SCREEN_PIECE_SIZE);
			}
		}
	};
	
	inline void drawCursor()
	{
		Vec2Int screenPosition = coordinateToScreenPosition(_gameState->cursor.xCoord, _gameState->cursor.yCoord);
		renderer::spriteBatch_draw(_gameState->spriteBatch,
								    &_gameState->cursor.sprite,
								    screenPosition.x, screenPosition.y,
								    CURSOR_WIDTH, CURSOR_HEIGHT);
	};
	
	void draw()
	{
		renderer::clearBuffers(renderer::Context::COLOR_BUFFER | renderer::Context::DEPTH_BUFFER);
		renderer::beginFrame(_gameState->projMatrix);
		renderer::spriteBatch_begin(_gameState->spriteBatch);
		drawCursor();
		drawBoardPieces();
		
		renderer::spriteBatch_end(_gameState->spriteBatch);
		renderer::endFrame();
	};
};
