static const uint32 WINDOW_WIDTH = 600;
static const uint32 WINDOW_HEIGHT = 800;
static const float ASPECT_RATIO = 1.0f;
static const uint32 PIECE_SIZE = 16;
static const uint32 SCREEN_PIECE_SIZE = 32;

namespace view
{
	void initializePieceSprites()
	{
		for (int i = 0; i < PieceType::PIECE_TYPE_LENGTH; i++)
		{
			renderer::makeSprite(&_gameState->sprites[i], _gameState->material, (i*19), 0, PIECE_SIZE, PIECE_SIZE);
		}
	};

	void initializeBoardSprites()
	{
		Vec4 clearColor = Vec4{0.0f, 0.0f, 0.0f, 0.0f};
		renderer::context_initialize(255, clearColor, 0);
		  
		_gameState->material = loadMaterial("./assets/piece.mat");
		 
		_gameState->projMatrix.orthographic(0, 600, 0, 800, -10, 10);
		renderer::material_setMatrix4(_gameState->material, "mprojection", &_gameState->projMatrix);
		// model
		_gameState->modelMatrix.identity();
		_gameState->modelMatrix.translate(Vec3{0, 0, -2});
		renderer::material_setMatrix4(_gameState->material, "mmodel", &_gameState->modelMatrix);

		// Initialize the sprite batch
		_gameState->spriteBatch = renderer::spriteBatch_create(16);
		
		initializePieceSprites();
	};

	void draw()
	{
		renderer::clearBuffers(renderer::Context::COLOR_BUFFER | renderer::Context::DEPTH_BUFFER);
		renderer::spriteBatch_begin(_gameState->spriteBatch);
		renderer::spriteBatch_draw(_gameState->spriteBatch ,&_gameState -> sprites[0], 5 + (SCREEN_PIECE_SIZE * 0) , 5, SCREEN_PIECE_SIZE, SCREEN_PIECE_SIZE, 0);
		renderer::spriteBatch_draw(_gameState->spriteBatch ,&_gameState -> sprites[0], 5 + (SCREEN_PIECE_SIZE * 1) , 5, SCREEN_PIECE_SIZE, SCREEN_PIECE_SIZE, 0);
		//renderer::spriteBatch_draw(_gameState->spriteBatch ,&_gameState -> sprites[1], 5 + (SCREEN_PIECE_SIZE * 1) , 5, SCREEN_PIECE_SIZE, SCREEN_PIECE_SIZE, 0);
		renderer::spriteBatch_end(_gameState->spriteBatch);
	};
};
