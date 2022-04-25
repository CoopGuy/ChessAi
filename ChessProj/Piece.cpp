#include "Piece.h"
#include <string>
#include <vector>
#include "Board.h"
#include "TheoreticalBoard.h"

//#include <Windows.h>
//#include <iostream>
//#include <wchar.h>
//#include <io.h>
//#include <fcntl.h>

//constructors
Piece::Piece()
{
	type = pieceType::empty;
	color = "None";
	hasMoved = false;
	isCaptured = false;
	l = Location();
}
Piece::Piece( pieceType type )
{
	this->type = type;
	hasMoved = false;
	isCaptured = false;
	l = Location();
}
Piece::Piece( pieceType type, std::string color )
{
	this->type = type;
	this->color = color;
	hasMoved = false;
	isCaptured = false;
	l = Location();
}
Piece::Piece( const Piece &Obj )
{
	type = Obj.type;
	color = Obj.color;
	hasMoved = Obj.hasMoved;
	isCaptured = Obj.isCaptured;
	l = Obj.l;
}
//overrides
void Piece::operator=( const Piece &Obj )
{
	type = Obj.type;
	color = Obj.color;
	hasMoved = Obj.hasMoved;
}
bool Piece::operator==( Piece &Obj )
{
	return ( l == Obj.l );
}
void Piece::print() const
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

//Movement functions

std::vector<Location> Piece::getPossibleDiagsFromPos( Board *boardRef, int lim )
{
	bool upRight = true;
	bool upLeft = true;
	bool dnright = true;
	bool dnleft = true;

	std::vector<Location> list;
	list.reserve( 15 );

	int counter = 1;
	Location temp;
	Piece *tempPiece = nullptr;

	while ( ( upRight || upLeft || dnright || dnleft ) && counter <= lim )
	{

		temp.assignAll( l.fx(), l.fy(), l.fx() + counter, l.fy() + counter );
		if ( temp.inBounds( "TO" ) )tempPiece = boardRef->pieceAtLocation( temp, true );
		else upRight = false;
		upRight = upRight && ( tempPiece->getType() == Piece::empty || tempPiece->getColor() != color );

		if ( upRight )
		{
			Location t( temp );
			list.push_back( t );
			if ( tempPiece->getColor() != color && tempPiece->getColor() != "None" ) upRight = false;
		}

		temp.assignAll( l.fx(), l.fy(), l.fx() + counter, l.fy() - counter );
		if ( temp.inBounds( "TO" ) )tempPiece = boardRef->pieceAtLocation( temp, true );
		else upLeft = false;
		upLeft = upLeft && ( tempPiece->getType() == Piece::empty || tempPiece->getColor() != color );

		if ( upLeft )
		{
			Location t( temp );
			list.push_back( t );
			if ( tempPiece->getColor() != color && tempPiece->getColor() != "None" ) upLeft = false;
		}

		temp.assignAll( l.fx(), l.fy(), l.fx() - counter, l.fy() + counter );
		if ( temp.inBounds( "TO" ) )tempPiece = boardRef->pieceAtLocation( temp, true );
		else dnright = false;
		dnright = dnright && ( tempPiece->getType() == Piece::empty || tempPiece->getColor() != color );

		if ( dnright )
		{
			Location t( temp );
			list.push_back( t );
			if ( tempPiece->getColor() != color && tempPiece->getColor() != "None" ) dnright = false;
		}

		temp.assignAll( l.fx(), l.fy(), l.fx() - counter, l.fy() - counter );
		if ( temp.inBounds( "TO" ) ) tempPiece = boardRef->pieceAtLocation( temp, true );
		else dnleft = false;
		dnleft = dnleft && ( tempPiece->getType() == Piece::empty || tempPiece->getColor() != color );
		if ( dnleft )
		{
			Location t( temp );
			list.push_back( t );
			if ( tempPiece->getColor() != color && tempPiece->getColor() != "None" ) dnleft = false;
		}
		counter++;
	}

	return list;
}

std::vector<Location> Piece::getPossibleLinearsFromPos( Board *boardRef,  int lim )
{
	bool Left = true;
	bool Right = true;
	bool Up = true;
	bool Down = true;

	std::vector<Location> list;
	list.reserve( 15 );

	int counter = 1;
	Location temp;
	Piece *tempPiece = nullptr;

	while ( ( Left || Right || Up || Down ) && counter <= lim )
	{

		temp.assignAll( l.fx(), l.fy(), l.fx() + counter, l.fy() );
		if ( temp.inBounds( "TO" ) )tempPiece = boardRef->pieceAtLocation( temp, true );
		else Left = false;
		Left = Left && ( tempPiece->getType() == Piece::empty || tempPiece->getColor() != color );

		if ( Left )
		{
			Location t( temp );
			list.push_back( t );
			if ( tempPiece->getColor() != color && tempPiece->getColor() != "None" ) Left = false;
		}

		temp.assignAll( l.fx(), l.fy(), l.fx() - counter, l.fy() );
		if ( temp.inBounds( "TO" ) )tempPiece = boardRef->pieceAtLocation( temp, true );
		else Right = false;
		Right = Right && ( tempPiece->getType() == Piece::empty || tempPiece->getColor() != color );

		if ( Right )
		{
			Location t( temp );
			list.push_back( t );
			if ( tempPiece->getColor() != color && tempPiece->getColor() != "None" ) Right = false;
		}

		temp.assignAll( l.fx(), l.fy(), l.fx(), l.fy() + counter );
		if ( temp.inBounds( "TO" ) )tempPiece = boardRef->pieceAtLocation( temp, true );
		else Up = false;
		Up = Up && ( tempPiece->getType() == Piece::empty || tempPiece->getColor() != color );

		if ( Up )
		{
			Location t( temp );
			list.push_back( t );
			if ( tempPiece->getColor() != color && tempPiece->getColor() != "None" ) Up = false;
		}

		temp.assignAll( l.fx(), l.fy(), l.fx(), l.fy() - counter );
		if ( temp.inBounds( "TO" ) )tempPiece = boardRef->pieceAtLocation( temp, true );
		else Down = false;
		Down = Down && ( tempPiece->getType() == Piece::empty || tempPiece->getColor() != color );
		if ( Down )
		{
			Location t( temp );
			list.push_back( t );
			if ( tempPiece->getColor() != color && tempPiece->getColor() != "None" ) Down = false;
		}
		counter++;
	}


	return list;
}

std::vector<Location> Piece::getPossibleKnightMoves( Board *boardRef )
{
	std::vector<Location> output;

	Location temp;
	temp = Location( l.fx(), l.fy(), l.fx() + 1, l.fy() + 2 );
	if ( temp.inBounds( "TO" ) )output.push_back( temp );
	temp = Location( l.fx(), l.fy(), l.fx() + 1, l.fy() - 2 );
	if ( temp.inBounds( "TO" ) )output.push_back( temp );
	temp = Location( l.fx(), l.fy(), l.fx() - 1, l.fy() + 2 );
	if ( temp.inBounds( "TO" ) )output.push_back( temp );
	temp = Location( l.fx(), l.fy(), l.fx() - 1, l.fy() - 2 );
	if ( temp.inBounds( "TO" ) )output.push_back( temp );
	temp = Location( l.fx(), l.fy(), l.fx() + 2, l.fy() + 1 );
	if ( temp.inBounds( "TO" ) )output.push_back( temp );
	temp = Location( l.fx(), l.fy(), l.fx() + 2, l.fy() - 1 );
	if ( temp.inBounds( "TO" ) )output.push_back( temp );
	temp = Location( l.fx(), l.fy(), l.fx() - 2, l.fy() + 1 );
	if ( temp.inBounds( "TO" ) )output.push_back( temp );
	temp = Location( l.fx(), l.fy(), l.fx() - 2, l.fy() - 1 );
	if ( temp.inBounds( "TO" ) )output.push_back( temp );

	for ( int x = output.size() - 1; x >= 0; x-- )
	{
		if ( boardRef->pieceAtLocation( output.at( x ), true )->getColor() == color )
		{
			output.erase( output.begin() + x );
		}
	}

	return output;
}

std::vector<Location> Piece::getPossiblePawnMoves( Board *boardRef )
{
	std::vector<Location> list;
	list.reserve( 4 );

	// pos is positive (1) if turn is white and negative (-1) if turn is black
	// essentially decides what "forward" is based on the turn
	int pos = 1 + ( -2 * ( color != "White" ) );
	Location tempLocation;

	//checks for forward movement of a pawn
	tempLocation = Location( l.fx(), l.fy(), l.fx(), l.fy() + pos );
	if ( tempLocation.inBounds( "TO" ) && boardRef->pieceAtLocation( tempLocation, true )->getColor() == "None" )list.push_back( Location( tempLocation ) );

	tempLocation = Location( l.fx(), l.fy(), l.fx(), l.fy() + ( 2 * pos ) );
	if ( tempLocation.inBounds( "TO" ) && !( boardRef->pieceAtLocation( l, false )->getHasMoved() ) && boardRef->pieceAtLocation( tempLocation, true )->getType() == Piece::empty ) list.push_back( Location( tempLocation ) );

	//check for diagonal attack positive slope (and en passant)
	tempLocation = Location( l.fx(), l.fy(), l.fx() + 1, l.fy() + pos );
	if ( tempLocation.inBounds( "TO" ) && ( boardRef->pieceAtLocation( tempLocation, true )->getColor() != color && boardRef->pieceAtLocation( tempLocation, true )->getColor() != "None" ) ||
		( boardRef->pawnMove().ty() == tempLocation.fy() && boardRef->pawnMove().tx() - tempLocation.fx() == 1 ) )list.push_back( tempLocation );


	//check for diagonal attack negative slope (and en passant)
	tempLocation = Location( l.fx(), l.fy(), l.fx() - 1, l.fy() + pos );
	if ( tempLocation.inBounds("TO") && ( boardRef->pieceAtLocation(tempLocation, true)->getColor() != color && boardRef->pieceAtLocation(tempLocation, true)->getColor() != "None" ) ||
		( boardRef->pawnMove().ty() == tempLocation.fy() && boardRef->pawnMove().tx() - tempLocation.fx() == -1) )list.push_back( tempLocation );

	return list;
}

std::vector<Location> Piece::getPossibleKingMoves( Board *boardRef )
{
	std::vector<Location> list = getPossibleDiagsFromPos( boardRef, 1 );
	std::vector<Location> temp = getPossibleLinearsFromPos( boardRef, 1 );
	list.insert( list.end(), temp.begin(), temp.end() );

	return list;
}

std::vector<Location> Piece::getMovesOfPiece( std::string turn, Board *boardRef, bool checks )
{
	std::vector<Location> temp;
	switch ( boardRef->pieceAtLocation( l, false )->getType() )
	{
		case Piece::pawn:
		temp = getPossiblePawnMoves( boardRef );
		break;
		case Piece::knight:
		temp = getPossibleKnightMoves( boardRef );
		break;
		case Piece::bishop:
		temp = getPossibleDiagsFromPos( boardRef );
		break;
		case Piece::rook:
		temp = getPossibleLinearsFromPos( boardRef );
		break;
		case Piece::queen:
		{
			std::vector<Location> temp1 = getPossibleLinearsFromPos( boardRef );
			std::vector<Location> temp2 = getPossibleDiagsFromPos( boardRef );
			temp1.insert( temp1.begin(), temp2.begin(), temp2.end() );
			temp = temp1;
		}
		break;
		case Piece::king:
		{
			temp = getPossibleKingMoves( boardRef );
		}
		break;
	}
	for ( int x = temp.size() - 1; x >= 0; x-- )
	{
		if ( checks && TheoreticalBoard( boardRef, temp.at( x ) ).KingIsInCheck() )
		{
			temp.erase( temp.begin() + x );
		}
	}
	return temp;
}

bool Piece::checkMove(Location &l, Board *boardRef)
{
	return moveInList( l, getMovesOfPiece( boardRef->turn(), boardRef) );
}



// checks if a move is present in a list (only checks the pos that the piece is going to)
bool Piece::moveInList( Location &l, std::vector<Location> list )
{
	for ( unsigned int x = 0; x < list.size(); x++ )
	{
		if ( l.tx() == list.at( x ).tx() && l.ty() == list.at( x ).ty() )return true;
	}
	return false;
}


/*
		std::string otherPlayersTurn = "White";
		if ( turn == otherPlayersTurn )otherPlayersTurn = "Black";

		temp = getAllMoves( boardRef, otherPlayersTurn );

		for ( int x = list.size() - 1; x >= 0; x-- )
		{
			for ( int y = 0; y < temp.size(); y++ )
			{
				if ( list.at( x ).tx() == temp.at( y ).tx() && list.at( x ).ty() == temp.at( y ).ty() )
				{
					list.erase( list.begin() + x );
					break;
				}
			}
		}
*/