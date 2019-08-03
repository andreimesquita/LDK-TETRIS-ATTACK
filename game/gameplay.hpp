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
	};
	
	//********************
	// Update Logic
	//********************
	void moveCursor()
	{
		Cursor &cursor = _gameState->cursor;
		
		if (input::isKeyDown(input::LDK_KEY_UP))
		{
			cursor.yCoord += 1;
		}
		else if (input::isKeyDown(input::LDK_KEY_DOWN))
		{
			cursor.yCoord -= 1;
		}
		
		if (input::isKeyDown(input::LDK_KEY_LEFT))
		{
			cursor.xCoord -= 1;
		}
		else if (input::isKeyDown(input::LDK_KEY_RIGHT))
		{
			cursor.xCoord += 1;
		}
	};
	
	void updateLogic(float deltaTime)
	{
		moveCursor();
		
		//TODO(andrei) move pieces upwards
		//if the game is still running (pieces moving OR paused due to piece matching)
			//TODO(andrei) Check if game is over (pieces have reached the top limit)
			//TODO(andrei) Check for input
				//Check matches
	};
};
