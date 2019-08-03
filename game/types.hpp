//board
static const uint32 BOARD_LINES = 12;
static const uint32 BOARD_COLUMNS = 6;
static const uint32 LINES_ARRAY_LENGTH = 24;

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
	PIECE_TYPE_LENGTH,
	EMPTY = 99,
};

struct Piece
{
	PieceType Type = PieceType::EMPTY;
};

struct Line
{
	uint32 CoordY = 0;
	Piece PiecesArr[BOARD_COLUMNS];
};

static Line EMPTY_LINE;

static struct GameState
{
	renderer::SpriteBatch* spriteBatch;
	Mat4 projMatrix;
	HMaterial material;
	renderer::Sprite sprites[PIECE_TYPE_LENGTH];
	Line lines[LINES_ARRAY_LENGTH];
} *_gameState;
