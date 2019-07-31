//board
static const uint32 BOARD_LINES = 12;
static const uint32 BOARD_COLUMNS = 6;

//piece & piece type
enum PieceType
{
	GREEN = 0,
	PURPLE,
	RED,
	YELLOW,
	LIGHT_BLUE,
	DARK_BLUE,
	EXCLAMATION_MARK,
	PIECE_TYPE_LENGTH
};

struct Piece
{
	PieceType Type;
};

struct Line
{
	uint32 CoordY;
	Piece *PiecesArr;
};

static struct GameState
{
	renderer::SpriteBatch* spriteBatch;
	Mat4 modelMatrix;
	Mat4 projMatrix;
	HMaterial material;
	renderer::Sprite sprites[PieceType::PIECE_TYPE_LENGTH];
} *_gameState;
