#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

#include "Board.h"
#include "Piece.h"

Board::Board()
{
	gameEnded = false;
	check = false;

	activeTurn = "White";

	pawnThatMoved = Location();
	didEnpassant = false;

	emptySquare = new Piece();
	setVals();
}

Board::Board( const Board &Obj )
{
	gameEnded = Obj.gameEnded;
	check = Obj.check;

	activeTurn = Obj.activeTurn;

	pawnThatMoved = Obj.pawnThatMoved;
	didEnpassant = Obj.didEnpassant;

	emptySquare = Obj.emptySquare;
	for ( int x = 0; x < Obj.whitePieces.size(); x++ )
	{
		whitePieces.push_back( Obj.whitePieces.at( x ) );
		blackPieces.push_back( Obj.blackPieces.at( x ) );
		for ( int x = 0; x < 8; x++ )
		{
			for ( int y = 0; y < 8; y++ )
			{
				boardarr[y][x] = Obj.boardarr[y][x];
			}
		}
	}
}

void Board::setVals()
{
	whitePieces.push_back( new Piece( Piece::rook,	"White" ) );
	whitePieces.push_back( new Piece( Piece::knight,"White" ) );
	whitePieces.push_back( new Piece( Piece::bishop,"White" ) );
	whitePieces.push_back( new Piece( Piece::king,	"White" ) );
	whitePieces.push_back( new Piece( Piece::queen,	"White" ) );
	whitePieces.push_back( new Piece( Piece::bishop,"White" ) );
	whitePieces.push_back( new Piece( Piece::knight,"White" ) );
	whitePieces.push_back( new Piece( Piece::rook,	"White" ) );

	blackPieces.push_back( new Piece( Piece::rook,	"Black" ) );
	blackPieces.push_back( new Piece( Piece::knight,"Black" ) );
	blackPieces.push_back( new Piece( Piece::bishop,"Black" ) );
	blackPieces.push_back( new Piece( Piece::king,	"Black" ) );
	blackPieces.push_back( new Piece( Piece::queen,	"Black" ) );
	blackPieces.push_back( new Piece( Piece::bishop,"Black" ) );
	blackPieces.push_back( new Piece( Piece::knight,"Black" ) );
	blackPieces.push_back( new Piece( Piece::rook,	"Black" ) );
	
	for ( int x = 0; x < 8; x++ )
	{
		whitePieces.push_back( new Piece( Piece::pawn, "White" ) );
		blackPieces.push_back( new Piece( Piece::pawn, "Black" ) );
	}
	for ( int x = 0; x < 8; x++ )
	{
		boardarr[0][x] = ( whitePieces.at( x ) );
		boardarr[1][x] = ( whitePieces.at( x + 8 ) );
		for ( int y = 2; y < 6; y++ )
		{
			boardarr[y][x] = emptySquare;
		}
		boardarr[6][x] = ( blackPieces.at( x + 8 ) );
		boardarr[7][x] = ( blackPieces.at( x ) );
	}
	Location temp;
	for ( int x = 0; x < 8; x++ )
	{
		temp.assignAll( x, 0 );
		whitePieces.at( x )->setLoc(temp,false);
		temp.assignAll( x, 1 );
		whitePieces.at( x + 8 )->setLoc( temp, false );

		temp.assignAll( x, 6 );
		blackPieces.at( x + 8)->setLoc( temp, false );
		temp.assignAll( x, 7 );
		blackPieces.at( x )->setLoc( temp, false );
	}

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
			boardarr[x][y]->print();
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
//if tf is (t)rue  returns ref to piece at location that location is going  (t)o
//it tf is (f)alse returns ref to piece at location that location is coming (f)rom
Piece *Board::pieceAtLocation( Location &var, bool tf )
{
	if ( !tf )
	{
		return boardarr[var.fy()][var.fx()];
	}
	return boardarr[var.ty()][var.tx()];
	
}



//checks if inputted move is valid
bool Board::validityTest( std::string move )
{
	bool moveValidity = false;
	Location location;
	
	if ( !parse( move, location ) )return false;
	
	Piece *tem = boardarr[location.fy()][location.fx()];
	Piece *tem2 = boardarr[location.ty()][location.tx()];

	Piece::pieceType piece = tem->getType();
	std::string color = tem->getColor();

	//check if turn and piece color match
	if ( activeTurn != color ) return false;
	// check if space that piece is moving to is occupied
	if ( tem->getColor() == tem2->getColor() && tem2->getType() != Piece::empty ) return false;

	
	moveValidity = checkMove( location );
	if ( moveValidity && piece == Piece::pawn )
	{
		if ( abs( location.fy() - location.ty() ) == 2 )pawnThatMoved = location;
		if ( location.fx() != location.tx() && pieceAtLocation( location, true )->getType() == Piece::empty ) didEnpassant = true;
	}

	if ( moveValidity && pawnThatMoved != location ) pawnThatMoved = Location();
	return moveValidity;
}

// calls the checkmove function of the piece at point (l.fx, l.fy)
bool Board::checkMove( Location &l )
{
	return pieceAtLocation( l, false )->checkMove( l, this );
}

//edits board array to reflect a completed move
void Board::doMove( std::string move, bool needsTest)
{
	if ( needsTest )validityTest( move );
	Location coords;
	parse( move, coords );

	//check for enpassant
	if ( didEnpassant )
	{
		//change the pieces
		int pos = 1 + ( -2 * ( activeTurn != "White" ) );
		didEnpassant = false;

		boardarr[coords.ty() - pos][coords.tx()]->capture();
		boardarr[coords.ty() - pos][coords.tx()] = emptySquare;
	}
	else
	{
		boardarr[coords.ty()][coords.tx()]->capture();
	}

	boardarr[coords.ty()][coords.tx()] = boardarr[coords.fy()][coords.fx()];
	boardarr[coords.fy()][coords.fx()] = emptySquare;
	boardarr[coords.ty()][coords.tx()]->moved();

	//check if pawn is at end of board
	if ( boardarr[coords.tx()][coords.ty()]->getType() == Piece::pawn && (coords.tx() == 7 || coords.tx() == 0))
	{
		boardarr[coords.tx()][coords.ty()]->setType( changePawn() );
	}
	
	//update location stored in piece class
	boardarr[coords.ty()][coords.tx()]->setLoc( coords );

	//change turn
	if ( activeTurn == "Black" )activeTurn = "White";
	else activeTurn = "Black";
}

// changes piece type for pawns that got to the 8th rank
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



//converts user input board locations to valid array addresses ie: a1c5 --> [[0,0],[3,4]]
bool Board::parse( std::string move, Location &location)
{
	if ( conv( move[0] ) + 1 &&  conv( move[1] ) + 1 && conv( move[2] ) + 1 &&  conv( move[3] ) + 1 )//check  to ensure input is allowed chars and addresses are in board width/length
	{
		location.assignAll( conv( move[0] ), conv( move[1] ), conv( move[2] ), conv( move[3] ) ); // conversion to chars for array addressing
		return true;
	}
	return false;
}

// converts user input chars a - h and nums 1 - 8 to chars in range 0 - 7 for boardarr addressing (allows for capital and lowercase)
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



std::vector<Location> Board::getAllMoves( std::string turn )
{
	//output vector init
	std::vector<Location> outputVec;
	// reserve avg possible moves for a player +10 for program efficiency
	outputVec.reserve( 50 ); 
	// get a vector of refs to the 'turn' colored pieces
	std::vector<Piece*> *list = this->getPieceVec( turn ); 

	std::vector<Location> temp;
	for ( int x = 0; x < list->size(); x++ )
	{
		//get moves of a given piece
		temp = list->at( x )->getMovesOfPiece( turn, this, false );

		//insert moves into output vector
		outputVec.insert( outputVec.end(), temp.begin(), temp.end() );
	}
	return outputVec;
}