#include <string>
#include <iostream>
#include <algorithm>
#include "Board.h"
#include "Piece.h"

Board::Board()
{
	gameEnded = false;
	activeTurn = "White";
	pawnMoved2 = false;
	check = false;
	setVals();
}

void Board::setVals()
{
	for ( int x = 0; x < 8; x++ )
	{
		boardarr[1][x].setType( Piece::pawn );
		boardarr[6][x].setType( Piece::pawn );
		boardarr[0][x].setColor( "White" );
		boardarr[1][x].setColor( "White" );

		boardarr[6][x].setColor( "Black" );
		boardarr[7][x].setColor( "Black" );
	}
	boardarr[0][0].setType( Piece::rook );
	boardarr[0][7].setType( Piece::rook );
	boardarr[7][0].setType( Piece::rook );
	boardarr[7][7].setType( Piece::rook );
	
	boardarr[0][1].setType( Piece::knight );
	boardarr[0][6].setType( Piece::knight );
	boardarr[7][1].setType( Piece::knight );
	boardarr[7][6].setType( Piece::knight );

	boardarr[0][2].setType( Piece::bishop );
	boardarr[0][5].setType( Piece::bishop );
	boardarr[7][2].setType( Piece::bishop );
	boardarr[7][5].setType( Piece::bishop );

	boardarr[0][3].setType( Piece::king );
	boardarr[0][4].setType( Piece::queen );
	boardarr[7][3].setType( Piece::king );
	boardarr[7][4].setType( Piece::queen );

	boardarr[4][4].setType( Piece::queen );
	boardarr[4][4].setColor( "Black" );
}

void Board::printBoard()
{
	std::cout.flush();
	//_setmode( _fileno( stdout ), _O_TEXT );
	std::cout << "   ";
	for ( int y = 0; y < 8; y++ )
	{
		char temp = 65 + y;
		std::cout << "  " << temp << " ";
	}
	std::cout << std::endl;
	std::cout << "   ";
	for ( int y = 0; y < 8; y++ )
	{
		std::cout << "----";
	}
	std::cout << "-" << std::endl;
	for ( int x = 0; x < 8; x++ )
	{
		std::cout << " " << x + 1 << " ";


		std::cout << "| ";
		for ( int y = 0; y < 8; y++ )
		{
			boardarr[x][y].print();
		}
		std::cout << std::endl;
		std::cout << "   ";
		for ( int y = 0; y < 8; y++ )
		{
			std::cout << "----";
		}
		std::cout << "-";
		std::cout << std::endl;
	}
}

//checks if inputted move is valid
bool Board::validityTest( std::string move )
{
	bool moveValidity = false;
	Location location;
	
	if ( !parse( move, location ) )return false;
	
	Piece *tem = &boardarr[location.fromx()][location.fromy()];
	Piece *tem2 = &boardarr[location.tox()][location.toy()];

	Piece::pieceType piece = tem->getType();
	std::string color = tem->getColor();

	if ( activeTurn != color ) return false;//check if turn and piece color match
	if ( color == tem2->getColor() && tem2->getType() != Piece::empty ) return false;//check if piece to be moved exists

	switch ( piece )
	{
		case Piece::empty:
		{
			moveValidity = false;
		}
		break;

		case Piece::pawn:
		{
			moveValidity = checkPawn( location, activeTurn);
		}
		break;

		case Piece::knight:
		{
			moveValidity = checkKnight( location );
		}
		break;

		case Piece::bishop:
		{
			moveValidity = checkBishop( location );
		}
		break;

		case Piece::rook:
		{
			moveValidity = checkRook( location );
		}
		break;

		case Piece::queen:
		{
			moveValidity = checkQueen( location );
		}
		break;

		case Piece::king:
		{
			moveValidity = checkKing( location );
		}
		break;

		default:
		{ moveValidity = false; }
		break;
	}

	return moveValidity;
}

//edits board array to reflect a completed move
void Board::doMove( std::string move, bool needsTest)
{
	if ( needsTest )validityTest( move );
	Location coords;
	parse( move, coords );

	//change the pieces
	boardarr[coords.tox()][coords.toy()] = boardarr[coords.fromx()][coords.fromy()];
	boardarr[coords.fromx()][coords.fromy()] = Piece();
	
	//check if pawn is at end of board
	if ( boardarr[coords.tox()][coords.toy()].getType() == Piece::pawn && (coords.tox() == 7 || coords.tox() == 0))
	{
		boardarr[coords.tox()][coords.toy()].setType( changePawn() );
	}

	//change turn
	if ( activeTurn == "Black" )activeTurn = "White";
	else activeTurn = "Black";
}

// changes pawns that got to the 8th rank
Piece::pieceType Board::changePawn()
{

	char a;
	bool b = false;
	do
	{
		do
		{
			if ( b )std::cout << "Invalid piece try again: ";
			else std::cout << "A Pawn has reached the 8th rank. What will it turn into(k,b,r,q): ";
			std::cin >> a;

			std::cin.clear();                              //clear errors/bad flags on cin

			std::cin.ignore( std::cin.rdbuf()->in_avail(), '\n' );//precise amount of ignoring
			std::cin.rdbuf()->in_avail(); //returns the exact number of characters in the cin buffer.

			b = true;
		} while ( !isalpha( a ) );

		if ( isupper( a ) )a += ' ';

		switch ( a )
		{
			case 'k':
			return Piece::knight;
			break;
			case 'b':
			return Piece::bishop;
			break;
			case 'r':
			return Piece::rook;
			break;
			case 'q':
			return Piece::queen;
			break;
			default:
			break;
		}
	} while ( true );
}

//converts user input board locations to valid array addresses ie: a1c5 --> loc[][] = [[0,0],[3,4]]
bool Board::parse( std::string move, Location &location)
{
	if ( conv( move[0] ) + 1 &&  conv( move[1] ) + 1 && conv( move[2] ) + 1 &&  conv( move[3] ) + 1 )//check  to ensure input is allowed chars and addresses are in board width/length
	{
		location.assignAll( conv( move[0] ), conv( move[1] ), conv( move[2] ), conv( move[3] ) ); // conversion to chars for array addressing
		return true;
	}
	return false;
}

// converts user input chars a - h and nums 1 - 8 to 0 - 7 for boardarr addressing (allows for capital and lowercase)
int Board::conv( char a )
{
	//check for 1st 8 nums and upper/lower case chars
	//and convert to range 0-7
	if		( a > 96 && a < 105 )a -= 97;
	else if ( a > 64 && a < 73  )a -= 65;
	else if ( a > 47 && a < 57  )a -= 49;
	else return -1;
	return a;
}

bool Board::checkDiagonal( Location loc )
{
	const int y1 = loc.fromy();
	const int x1 = loc.fromx();
	const int y2 = loc.toy();
	const int x2 = loc.tox();

	Piece targetSquare = boardarr[x2][y2];
	//checks for perfectly diagonal direction
	if ( ( x2 - x1 ) != 0 && abs( ( y2 - y1 ) / ( x2 - x1 ) ) != 1 )return false;
	//checks for empty or filled by opposite color piece on target square
	if ( targetSquare.getType() != Piece::empty && targetSquare.getColor() == activeTurn )return false;

	//checks for clear path
	//TODO: create checks for cleared paths
	//y-y1 = m(x-x1)
	int slope = ( y2 - y1 )/( x2 - x1 );

	int lowy = std::min( y1, y2 );
	int maxy = std::max( y1, y2 );
	int xTerm;
	if ( lowy == y1 )xTerm = x1;
	else xTerm = x2;

	int count = 1;
	for ( int y = lowy + 1; y < maxy; y ++ )
	{
		if ( boardarr[xTerm + ( count * slope )][y].getType() != Piece::empty )return false;
		count++;
	}

	return true;
}

bool Board::checkLinear( Location loc )
{
	const int y1 = loc.fromy();
	const int x1 = loc.fromx();
	const int y2 = loc.toy();
	const int x2 = loc.tox();

	if ( !(y1 == y2 ^ x1 == x2) )return false;
	return false;
}

/*
	All of the following functions do exactly what their name suggests they do

	All of the following functions (are/will be) able to take an in bounds input and judge
	whether a piece can do that given move then return a bool that matches that ability:
	true for yes, false for no (I would think this is obvious but you never know)
*/

bool Board::checkPawn( Location location, std::string activeTurn )
{
	const int y1 = location.fromy();
	const int y2 = location.toy();

	int temp = y2 - y1;
	//if temp is + piece is traversing up board if - then down
	if ( temp == 0 )
	{
		if ( y2 - y1 == 1 )return true;
		return false;
	}
	if ( ( activeTurn == "White" && temp < 0 ) || ( activeTurn == "Black" && temp > 0 ) )
	{
		return false;
	}
	//TODO: implement check for going forward and diagonal capturing only 1 space
	return checkDiagonal( location );
}//does what it says on the tin

bool Board::checkKnight( Location location )
{
	return false;
}

bool Board::checkBishop( Location location )
{
	return checkDiagonal( location );
}

bool Board::checkRook( Location location )
{
	return checkLinear( location );
}

bool Board::checkQueen( Location location )
{
	return checkDiagonal( location ) || checkLinear( location );
}

bool Board::checkKing( Location location )
{
	return false;
}
