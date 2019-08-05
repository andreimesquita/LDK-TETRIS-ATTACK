namespace gameplay
{
	inline int isPieceEmpty(const Piece &piece)
	{
		return piece.Type == PieceType::EMPTY;
	};

	inline int areSamePieces(const Piece &pieceA, const Piece &pieceB)
	{
		return pieceA.Type == pieceB.Type;
	};
	
	inline Piece& getPieceInLine(Line &line, const uint32 columnIndex)
	{
		return line.PiecesArr[columnIndex];
	};
	
	inline Line& getLineByCoordinate(const int lineIndex)
	{
		for (int i = 0; i < LINES_ARRAY_LENGTH; i++)
		{
			if (_gameState->lines[i].CoordY == lineIndex)
			{
				return _gameState->lines[i];
			}
		}
		return EMPTY_LINE;
	};
	
	inline bool isLineEmpty(Line &line)
	{
		for (int i = 0; i < BOARD_COLUMNS; i++)
		{
			Piece &piece = getPieceInLine(line, i);
			if (!isPieceEmpty(piece))
			{
				return false;
			}
		}
		return true;
	};
	
	void insertNewLine()
	{
		//TODO
	};
	
	void incrementAllLinesCoordY()
	{
		//TODO(andrei)
	};
	
	class MatchNode
	{
		Vec2Int coord;
	};
	
	void get(std::vector<Vec2Int> &match)
	{
		//TODO
	};
	
	void horizontalAsd(Piece &pieceLeft,
						std::unordered_set<Vec2Int> &knownCoordinates,
						std::vector<Vec2Int> &matches)
	{
		//left
		for (int i = (leftPiecePos.x - 1); i >= 0; i--)
		{
			Piece &leftPiece = getPieceInLine(line, i);
			
			if (leftPiece.Type != pieceLeft.Type) break;
			
			Vec2Int otherPiecePos = Vec2Int(i, line.CoordY);
			
			if (knownCoordinates.count(otherPiecePos) > 0) break;
			
			matches.push_back(otherPiecePos);
			knownCoordinates.emplace(otherPiecePos);
		}
		
		//right
		for (int i = (leftPiecePos.x + 1); i < BOARD_COLUMNS; i++)
		{
			Piece &otherPiece = getPieceInLine(line, i);
			
			if (otherPiece.Type != pieceLeft.Type) break;
			
			Vec2Int otherPiecePos = Vec2Int(i, line.CoordY);
			
			if (knownCoordinates.count(otherPiecePos) > 0) break;
			
			matches.push_back(otherPiecePos);
			knownCoordinates.emplace(otherPiecePos);
		}
	};
	
	void verticalAsd(Piece &pieceLeft,
						std::unordered_set<Vec2Int> &knownCoordinates,
						std::vector<Vec2Int> &matches)
	{
		//up
		for (int i = (sourcePiecePos.y + 1); i < BOARD_LINES; i++)
		{
			Line &upperLine = getLineByCoordinate(i);
			Piece &upperPiece = getPieceInLine(upperLine, sourcePiecePos.x);
			
			if (upperPiece.Type != pieceLeft.Type) break;
			
			Vec2Int upperPiecePos = Vec2Int(sourcePiecePos.x, i);
			
			if (knownCoordinates.count(upperPiecePos) > 0) break;
			
			matches.push_back(upperPiecePos);
			knownCoordinates.emplace(upperPiecePos);
		}
		
		//down
		for (int i = (sourcePiecePos.y - 1); i >= 0; i--)
		{
			Line &lowerLine = getLineByCoordinate(i);
			Piece &lowerPiece = getPieceInLine(lowerLine, sourcePiecePos.x);
			
			if (lowerPiece.Type != pieceLeft.Type) break;
			
			Vec2Int upperPiecePos = Vec2Int(sourcePiecePos.x, i);
			
			if (knownCoordinates.count(upperPiecePos) > 0) break;
			
			matches.push_back(upperPiecePos);
			knownCoordinates.emplace(upperPiecePos);
		}
	};
	
	void swapPieces(const uint32 lineIndex, const uint32 columnLeft, const uint32 columnRight)
	{
		Line &line = getLineByCoordinate(lineIndex);
		
		Piece &pieceLeft = getPieceInLine(line, columnLeft);
		Piece &pieceRight = getPieceInLine(line, columnRight);
		
		if (areSamePieces(pieceLeft, pieceRight)
			&& isPieceEmpty(pieceLeft))
		{
			return;
		}
		
		//swipe piece's type
		PieceType leftPieceType = pieceLeft.Type;
		pieceLeft.Type = pieceRight.Type;
		pieceRight.Type = leftPieceType;
		
		//TODO(andrei) animate piece swipe by:
		//TODO(andrei) block pieces' movement?
		//TODO(andrei) trigger pieces' animation?
		//TODO(andrei) find matches
		
		//FIND MATCHES FOR LEFT PIECE
		std::unordered_set<Vec2Int> knownCoordinates;
		std::vector<Vec2Int> matches;
		
		Vec2Int leftPiecePos = Vec2Int(columnLeft, lineIndex);
		knownCoordinates.emplace(leftPiecePos);
		matches.push_back(leftPiecePos);
		
		//check matches for the left piece
		horizontalAsd(pieceLeft, knownCoordinates, matches);
		verticalAsd(pieceLeft knownCoordinates, matches);
		
		if (matches.size() >= 3)
		{
			int foundPieces = matches.size();
			
			for (int i = 0; i < foundPieces; i++)
			{
				Vec2Int &piecePosition = matches[i];
				Line &line = getLineByCoordinate(piecePosition.y);
				Piece &piece = getPieceInLine(line, piecePosition.x);
				piece.Type = PieceType::EMPTY;
			}
		}
		
		//check matches for the right piece
		horizontalAsd(pieceRight, knownCoordinates, matches);
		verticalAsd(pieceRight knownCoordinates, matches);
		
		if (matches.size() >= 3)
		{
			int foundPieces = matches.size();
			
			for (int i = 0; i < foundPieces; i++)
			{
				Vec2Int &piecePosition = matches[i];
				Line &line = getLineByCoordinate(piecePosition.y);
				Piece &piece = getPieceInLine(line, piecePosition.x);
				piece.Type = PieceType::EMPTY;
			}
		}
		
		//findSameNeighbours(line, columnRight, matches);
	};
	
	//********************
	// Update Logic
	//********************
	inline void processKeyDownAndSetCoord(Cursor &cursor, int &coord, int increment, uint32 keyCode)
	{
		if (input::isKeyDown(keyCode))
		{
			coord += increment;
			cursor.totalHoldingDeltaTime = 0;
		}
	};
	
	inline void processKeyHolding(Cursor &cursor, int &coord, int increment, float &deltaTime, uint32 keyCode)
	{
		if (input::getKey(keyCode))
		{
			cursor.totalHoldingDeltaTime += deltaTime;
			float decrement = (cursor.totalHoldingDeltaTime - 0.15f);
			if (decrement < 0.0f) decrement = 0.0f;
			int steps = (int) (increment * (decrement / 0.04f));
			coord += steps;
		}
	};
	
	void moveCursor(float &deltaTime)
	{
		Cursor &cursor = _gameState->cursor;
		
		// handle button click
		processKeyDownAndSetCoord(cursor, cursor.yCoord, 1, input::LDK_KEY_UP);
		processKeyDownAndSetCoord(cursor, cursor.yCoord, -1, input::LDK_KEY_DOWN);
		processKeyDownAndSetCoord(cursor, cursor.xCoord, -1, input::LDK_KEY_LEFT);
		processKeyDownAndSetCoord(cursor, cursor.xCoord, 1, input::LDK_KEY_RIGHT);
		
		//handle button hold
		processKeyHolding(cursor, cursor.yCoord, 1, deltaTime, input::LDK_KEY_UP);
		processKeyHolding(cursor, cursor.yCoord, -1, deltaTime, input::LDK_KEY_DOWN);
		processKeyHolding(cursor, cursor.xCoord, -1, deltaTime, input::LDK_KEY_LEFT);
		processKeyHolding(cursor, cursor.xCoord, 1, deltaTime, input::LDK_KEY_RIGHT);
		
		//clamp coordinates
		cursor.xCoord = clamp(cursor.xCoord, 0, (BOARD_COLUMNS - 2));
		cursor.yCoord = clamp(cursor.yCoord, 0, (BOARD_LINES - 1));
	};
	
	void handleSwipePieces()
	{
		if (input::isKeyDown(input::LDK_KEY_CONTROL))
		{
			Cursor &cusor = _gameState->cursor;
			uint32 leftColumn = (uint32) cusor.xCoord;
			uint32 line = (uint32) cusor.yCoord;
			swapPieces(line, leftColumn, leftColumn + 1);
		}
	};
	
	void updateLogic(float &deltaTime)
	{
		moveCursor(deltaTime);
		handleSwipePieces();
		
		//TODO(andrei) move pieces upwards
		//if the game is still running (pieces moving OR paused due to piece matching)
			//TODO(andrei) Check if game is over (pieces have reached the top limit)
			//TODO(andrei) Check for input
				//Check matches
	};
};
