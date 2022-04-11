#include "Piece.h"
#include <string>

#include <Windows.h>
#include <iostream>
#include <wchar.h>
#include <io.h>
#include <fcntl.h>

Piece::Piece()
{
	type = pieceType::empty;
	color = "None";
}
Piece::Piece( pieceType type )
{
	this->type = type;
}

Piece::pieceType Piece::getType()
{
	return type;
}

void Piece::setType(pieceType newType)
{
	type = newType;
}

std::string Piece::getColor()
{
	return color;
}

void Piece::setColor( std::string newColor )
{
	color = newColor;
}

void Piece::operator=( const Piece &Obj )
{
	type = Obj.type;
	color = Obj.color;
}

void Piece::print()
{
	//// Set console code page to UTF-8 so console known how to interpret string data
	//std::cout.flush();
	//
	//SetConsoleCP( 936 );
	//SetConsoleOutputCP( 936 );
	//// Enable buffering to prevent VS from chopping up UTF-8 byte sequences
	////setvbuf( stdout, nullptr, _IOFBF, 1000 );
	switch ( type )
	{
		case Piece::empty:
		std::cout << " ";
		break;

		case Piece::pawn:
		std::cout << 'p';
		break;

		case Piece::knight:
		std::cout << 'k';
		break;

		case Piece::bishop:
		std::cout << 'b';
		break;

		case Piece::rook:
		std::cout << 'r';
		break;

		case Piece::queen:
		std::cout << 'q';
		break;

		case Piece::king:
		std::cout << 'K';
		break;

		default:
		std::cout << "X";
		break;
		
	}
	if		( color == "Black" )std::cout << "b| ";
	else if ( color == "White" )std::cout << "w| ";
	else						std::cout << " | ";
}