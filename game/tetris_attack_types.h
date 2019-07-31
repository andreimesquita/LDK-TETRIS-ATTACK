//board
static uint32 BOARD_LINES = 12;
static uint32 BOARD_COLUMNS = 6;

//piece & piece type
typedef enum
{
	GREEN = 0,
	PURPLE,
	RED,
	YELLOW,
	LIGHT_BLUE,
	DARK_BLUE,
	EXCLAMATION_MARK,
	PIECE_TYPE_LENGTH
} PieceType;

struct Piece
{
	PieceType Type;
};

struct Line
{
	uint32 CoordY;
	Piece *PiecesArr;
};
