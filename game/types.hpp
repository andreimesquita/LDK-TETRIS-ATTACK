//board
static const uint32 BOARD_LINES = 12;
static const uint32 BOARD_COLUMNS = 6;
static const uint32 LINES_ARRAY_LENGTH = 24;

//piece & piece type
enum PieceType
{
	EMPTY = 0,
	GREEN = 1,
	PURPLE = 2,
	RED = 3,
	YELLOW = 4,
	LIGHT_BLUE = 5,
	DARK_BLUE = 6,
	EXCLAMATION_MARK = 7,
	PIECE_TYPE_LENGTH = 8
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
