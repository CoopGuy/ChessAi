#pragma once
#include <string>

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

	private:
	pieceType type;
	std::string color;
	bool hasMoved;

	public:

	//constructor
	Piece();
	Piece( pieceType type );
	
	//getter and setter
	pieceType getType() { return type; };
	void setType( pieceType newType ) { type = newType; };
	std::string getColor() {	return color;	};
	void setColor( std::string newColor ){	color = newColor;	};
	bool getHasMoved(){	return hasMoved;	};
	void moved(){	hasMoved = true;	};

	//overrides
	void operator=( const Piece &Obj );
	void print() const;

};