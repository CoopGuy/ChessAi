#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Board.h"
#include "Piece.h"

Board::Board()
{
	gameEnded = false;
	activeTurn = "White";
	pawnThatMoved = Location();
	check = false;
	enpassant = false;
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

void Board::printBoard() const
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

//gets a ref to a piece at a location specified by a location object
//if tf is (t)rue  returns ref to piece at location that location is going to
//it tf is (f)alse returns ref to piece at location that location is coming from
Piece *Board::pieceAtLocation( Location &var, bool tf )
{
	Piece *temp;

	if ( !tf )
	{
		temp = &boardarr[var.fy()][var.fx()];
	}
	else
	{
		temp = &boardarr[var.ty()][var.tx()];
	}

	return temp;
}



//checks if inputted move is valid
bool Board::validityTest( std::string move )
{
	bool moveValidity = false;
	Location location;
	
	if ( !parse( move, location ) )return false;
	
	Piece *tem = &boardarr[location.fy()][location.fx()];
	Piece *tem2 = &boardarr[location.ty()][location.tx()];

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
			moveValidity = checkPawn( location );
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
	boardarr[coords.ty()][coords.tx()] = boardarr[coords.fy()][coords.fx()];
	boardarr[coords.fy()][coords.fx()] = Piece();
	
	//check for enpassant
	if ( enpassant )
	{
		enpassant = false;
		if ( activeTurn == "White" )
		{
			boardarr[coords.ty() - 1][coords.tx()] = Piece();
		}
		else
		{
			boardarr[coords.ty() + 1][coords.tx()] = Piece();
		}
	}
	
	//check if pawn is at end of board
	if ( boardarr[coords.tx()][coords.ty()].getType() == Piece::pawn && (coords.tx() == 7 || coords.tx() == 0))
	{
		boardarr[coords.tx()][coords.ty()].setType( changePawn() );
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



std::vector<Location> Board::getPossibleDiagsFromPos( Location &l, int lim)
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

	while ( (upRight || upLeft || dnright || dnleft) && counter <= lim )
	{

		temp.assignAll( l.fx() + counter, l.fy() + counter, l.tx(), l.ty() );
		tempPiece = pieceAtLocation( temp, false );
		upRight = upRight && temp.inBounds( "FROM" ) && ( tempPiece->getType() == Piece::empty || tempPiece->getColor() != activeTurn );

		if ( upRight )
		{
			Location t( temp );
			list.push_back( t );
		}

		temp.assignAll( l.fx() + counter, l.fy() - counter, l.tx(), l.ty() );
		tempPiece = pieceAtLocation( temp, false );
		upLeft = upLeft && temp.inBounds( "FROM" ) && ( tempPiece->getType() == Piece::empty || tempPiece->getColor() != activeTurn );

		if ( upLeft )
		{
			Location t( temp );
			list.push_back( t );
		}

		temp.assignAll( l.fx() - counter, l.fy() + counter, l.tx(), l.ty() );
		tempPiece = pieceAtLocation( temp, false );
		dnright = dnright && temp.inBounds( "FROM" ) && ( tempPiece->getType() == Piece::empty || tempPiece->getColor() != activeTurn );

		if ( dnright )
		{
			Location t( temp );
			list.push_back( t );
		}

		temp.assignAll( l.fx() - counter, l.fy() - counter, l.tx(), l.ty() );
		tempPiece = pieceAtLocation( temp, false );
		dnleft = dnleft && temp.inBounds( "FROM" ) && ( tempPiece->getType() == Piece::empty || tempPiece->getColor() != activeTurn );
		if ( dnleft )
		{
			Location t( temp );
			list.push_back( t );
		}
		counter++;
	}

	return list;
}

std::vector<Location> Board::getPossibleLinearsFromPos( Location &l, int lim )
{
	bool Left	= true;
	bool Right	= true;
	bool Up		= true;
	bool Down	= true;

	std::vector<Location> list;
	list.reserve( 15 );

	int counter = 1;
	Location temp;
	Piece *tempPiece = nullptr;

	while ( ( Left || Right || Up || Down ) && counter <= lim )
	{

		temp.assignAll( l.fx() + counter, l.fy(), l.tx(), l.ty() );
		tempPiece = pieceAtLocation( temp, false );
		Left = Left && temp.inBounds( "FROM" ) && ( tempPiece->getType() == Piece::empty || tempPiece->getColor() != activeTurn );

		if ( Left )
		{
			Location t( temp );
			list.push_back( t );
		}

		temp.assignAll( l.fx() - counter, l.fy(), l.tx(), l.ty() );
		tempPiece = pieceAtLocation( temp, false );
		Right = Right && temp.inBounds( "FROM" ) && ( tempPiece->getType() == Piece::empty || tempPiece->getColor() != activeTurn );

		if ( Right )
		{
			Location t( temp );
			list.push_back( t );
		}

		temp.assignAll( l.fx(), l.fy() + counter, l.tx(), l.ty() );
		tempPiece = pieceAtLocation( temp, false );
		Up = Up && temp.inBounds( "FROM" ) && ( tempPiece->getType() == Piece::empty || tempPiece->getColor() != activeTurn );

		if ( Up )
		{
			Location t( temp );
			list.push_back( t );
		}

		temp.assignAll( l.fx(), l.fy() - counter, l.tx(), l.ty() );
		tempPiece = pieceAtLocation( temp, false );
		Down = Down && temp.inBounds( "FROM" ) && ( tempPiece->getType() == Piece::empty || tempPiece->getColor() != activeTurn );
		if ( Down )
		{
			Location t( temp );
			list.push_back( t );
		}
		counter++;
	}


	return list;
}

bool Board::moveInList( Location &l, std::vector<Location> list ) const
{
	for ( unsigned int x = 0; x < list.size(); x++ )
	{
		if ( l.tx() == list.at(x).fx() && l.ty() == list.at(x).fy() )return true;
	}
	return false;
}



/*
	All of the following functions provide a legality check of a given inputted move for their respective pieces

	All of the following functions (are/will be) able to take an in bounds Location and judge
	whether a piece can do that given move then return a bool that matches that ability:
	true for yes, false for no (I would think this is obvious but you never know)
*/

bool Board::checkPawn( Location &l )
{

	int temp = l.ty() - l.fy();

	//if temp is + piece is traversing up board if - then down
	if ( temp == 0 || ( activeTurn == "White" && temp < 0 ) || ( activeTurn == "Black" && temp > 0 ) )
		return false;
	
	if ( moveInList( l, getPossibleLinearsFromPos( l, 2 ) ) && l.fx() == l.tx() )
	{
		if ( pieceAtLocation( l, true )->getType() != Piece::empty )return false;
		Piece *tempPiece = pieceAtLocation( l, false );
		if ( abs( temp ) == 2 )
		{
			if ( tempPiece->getHasMoved() == true )
			{
				return false;
			}
			pawnThatMoved = l;
			return true;
		}
		else
		{
			tempPiece->moved();
			return true;
		}
	}
	if ( moveInList( l, getPossibleDiagsFromPos( l, 1 ) ) )
	{
		Piece *locat = pieceAtLocation( l, true );
		// check if diag piece is not the same color
		if ( ( locat->getColor() != activeTurn && locat->getColor() != "None" ) )
		{
			return true;
		}
		//en passant 
		else if ( l.tx() == pawnThatMoved.tx() && abs( l.ty() - pawnThatMoved.ty() ) == 1 ) {
			enpassant = true;
			return true;
		}
	}
	return false;
}

bool Board::checkKnight( Location &l )
{
	return ( (( abs( l.fx() - l.tx() ) == 1 && abs( l.fy() - l.ty() ) == 2 ) || ( abs( l.fx() - l.tx() ) == 2 && abs( l.fy() - l.ty() ) == 1 )) && pieceAtLocation( l, true )->getColor() != activeTurn );
}

bool Board::checkBishop( Location &l )
{
	return moveInList( l, getPossibleDiagsFromPos( l ) );
}

bool Board::checkRook( Location &l )
{
	return moveInList( l, getPossibleLinearsFromPos( l ) );
}

bool Board::checkQueen( Location &l )
{
	return moveInList( l, getPossibleDiagsFromPos( l ) ) || moveInList( l, getPossibleLinearsFromPos( l ) );
}

bool Board::checkKing( Location &l )
{
	bool KingCanMoveTo		= moveInList( l, getPossibleDiagsFromPos( l, 1 ) ) || moveInList( l, getPossibleLinearsFromPos( l, 1 ) );
	bool OppPieceCanMoveTo	= false;
	return KingCanMoveTo && !OppPieceCanMoveTo;
}





//DEPRECATED
bool Board::checkDiagonal( Location loc )
{
	const int y1 = loc.fy();
	const int x1 = loc.fx();
	const int y2 = loc.ty();
	const int x2 = loc.tx();

	Piece targetSquare = boardarr[x2][y2];
	//checks for perfectly diagonal direction
	if ( ( x2 - x1 ) != 0 && abs( ( y2 - y1 ) / ( x2 - x1 ) ) != 1 )return false;
	//checks for empty or filled by opposite color piece on target square
	if ( targetSquare.getType() != Piece::empty && targetSquare.getColor() == activeTurn )return false;

	//checks for clear path
	//TODO: create checks for cleared paths
	//y-y1 = m(x-x1)
	int slope = ( y2 - y1 ) / ( x2 - x1 );

	int lowy = std::min( y1, y2 );
	int maxy = std::max( y1, y2 );
	int xTerm;
	if ( lowy == y1 )xTerm = x1;
	else xTerm = x2;

	int count = 1;
	for ( int y = lowy + 1; y < maxy; y++ )
	{
		if ( boardarr[xTerm + ( count * slope )][y].getType() != Piece::empty )return false;
		count++;
	}

	return true;
}

bool Board::checkLinear( Location loc )
{
	const int y1 = loc.fy();
	const int x1 = loc.fx();
	const int y2 = loc.ty();
	const int x2 = loc.tx();

	if ( !( ( y1 == y2 ) ^ ( x1 == x2 ) ) )return false;
	return false;
}
//DEPRECATED
