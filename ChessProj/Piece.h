#pragma once
#include <string>
#include <vector>

#include "Location.h"

class Board;

class Piece
{
	public:
	enum pieceType
	{
		empty,
		pawn,
		knight,
		bishop,
		rook,
		queen,
		king
	};

	protected:
	pieceType type;
	std::string color;
	bool hasMoved;
	bool isCaptured;
	Location l;

	public:

	//constructor
	Piece();
	Piece( pieceType type );
	Piece( pieceType type, std::string color );
	Piece( const Piece &Obj );

	//getter and setter
	pieceType getType()							{ return type; };
	void setType( pieceType newType )			{ type = newType; };

	std::string getColor()						{ return color;	};
	void setColor( std::string newColor )		{ color = newColor;	};

	bool getHasMoved()							{ return hasMoved;	};
	void moved()								{ hasMoved = true;	};

	void capture()								{ isCaptured = true; };
	bool getCap()								{ return isCaptured; };

	void setLoc( Location a, bool tf = true )	{ if ( tf )l = Location( a.tx(), a.ty() ); else l = Location( a.fx(), a.fy() ); };
	Location getLoc()							{ return l; };


	//movement functions

	std::vector<Location> getPossibleDiagsFromPos( Board *boardRef, int lim = 8 );
	std::vector<Location> getPossibleLinearsFromPos( Board *boardRef, int lim = 8 );
	std::vector<Location> getPossiblePawnMoves( Board *boardRef );
	std::vector<Location> getPossibleKnightMoves( Board *boardRef );
	std::vector<Location> getPossibleKingMoves( Board *boardRef );
	
	std::vector<Location> getMovesOfPiece( std::string turn, Board *boardRef, bool checks = true );
	bool static moveInList( Location &l, std::vector<Location> list );

	bool checkMove( Location &l, Board *boardRef );

	//overrides
	void operator=( const Piece &Obj );
	bool operator==( Piece &Obj );
	void print() const;

};