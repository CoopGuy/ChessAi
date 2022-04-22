#pragma once
#include "Piece.h"
#include "Board.h"
#include "Location.h"

#include <string>
#include <vector>

class TheoreticalBoard : public Board
{
	private:
	
	Piece *pieceFromMove;
	Piece *pieceAtMove;

	Location *move;


	public:
	//constructors
	TheoreticalBoard( Board *boardRef, Location &move );

	void instantiateBoard( Board *boardRef );

	Piece *getKing( std::string color )
	{ 
		if ( color == "White" )return whitePieces.at( 3 ); 
		return blackPieces.at( 3 ); 
	}
	bool KingIsInCheck();

	void doMove();

	int rating( std::string turn );

	TheoreticalBoard doMove( Location move )
	{
		return TheoreticalBoard( this, move );
	}
};