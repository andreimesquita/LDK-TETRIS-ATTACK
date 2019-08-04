//board
static const uint32 BOARD_LINES = 12;
static const uint32 BOARD_COLUMNS = 6;
static const uint32 LINES_ARRAY_LENGTH = 24;

class Vec2Int
{
	public:
	
		int x;
		int y;
		
		Vec2Int() { }
		
		Vec2Int(int _x, int _y)
		{
			x = _x;
			y = _y;
		}
		
		Vec2Int(const Vec2Int &other)
		{
			x = other.x;
			y = other.y;
		}
		
		Vec2Int& operator=(const Vec2Int& other) {
			x = other.x;
			y = other.y;
			return *this;
		};
		
		// this could be moved in to std::hash<Point>::operator()
		size_t operator()(const Vec2Int& pointToHash) const noexcept {
			size_t hash = (pointToHash.x + 10 * pointToHash.y);
			return hash;
		};
		
		bool operator<(const Vec2Int& other) {
			return ((x < other.x) || (x == other.x && y == other.y));
		};
		
		bool operator==(const Vec2Int &other) const
		{ 
			return (x == other.x && y == other.y);
		}
};

namespace std {
    template<> struct hash<Vec2Int>
    {
        std::size_t operator()(const Vec2Int& p) const noexcept
        {
            return p(p);
        }
    };
}

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
	float totalHoldingDeltaTime;
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
