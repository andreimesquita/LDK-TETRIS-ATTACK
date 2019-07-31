static const uint32 WINDOW_WIDTH = 600;
static const uint32 WINDOW_HEIGHT = 800;
static const float ASPECT_RATIO = 1.0f;

void draw()
{
	renderer::clearBuffers(renderer::Context::COLOR_BUFFER | renderer::Context::DEPTH_BUFFER);
	renderer::spriteBatch_begin(_gameState->spriteBatch);
	renderer::spriteBatch_draw(_gameState->spriteBatch ,&_gameState -> sprite, 10 ,10 ,32 ,32 ,0);
	renderer::spriteBatch_end(_gameState->spriteBatch);
};
