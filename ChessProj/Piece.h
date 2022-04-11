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

	//constructor
	Piece();
	Piece( pieceType type );
	
	//getter and setter
	pieceType getType();
	void setType( pieceType newType );
	std::string getColor();
	void setColor(std::string newColor);


	//overrides
	void operator=( const Piece &Obj );
	void print();

	private:
	pieceType type;
	std::string color;
};