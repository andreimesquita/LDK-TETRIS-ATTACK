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
	
	Piece() { }
	
	Piece(const Piece &piece)
	{
		Type = piece.Type;
	};
};

struct Line
{
	uint32 CoordY = 0;
	Piece PiecesArr[BOARD_COLUMNS];
	
	Line() { }
	
	Line(const Line &line)
	{
		CoordY = line.CoordY;
		for(int i = 0; i < BOARD_COLUMNS; i++)
		{
			PiecesArr[i] = line.PiecesArr[i];
		}
	};
};

static Line EMPTY_LINE;

struct Cursor
{
	int xCoord;
	int yCoord;
	renderer::Sprite sprite;
};

static struct GameState
{
	renderer::SpriteBatch* spriteBatch;
	Mat4 projMatrix;
	HMaterial material;
	Cursor cursor;
	renderer::Sprite sprites[PIECE_TYPE_LENGTH];
	Line lines[LINES_ARRAY_LENGTH];
} *_gameState;
