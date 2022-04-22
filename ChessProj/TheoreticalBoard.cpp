#include "Piece.h"
#include "Location.h"
#include "TheoreticalBoard.h"

#include <string>
#include <vector>

//constructor for creating a theoretical move board from a Board object or child
TheoreticalBoard::TheoreticalBoard( Board *boardRef, Location &move ) : Board( *boardRef )
{

	this->move = &move;

	pieceFromMove = new Piece(*pieceAtLocation( move, false ));
	Piece *temp = pieceAtLocation( move, true );
	if ( temp->getType() != Piece::empty ) pieceAtMove = new Piece( *temp );
	else pieceAtMove = temp;

	instantiateBoard( boardRef );
	doMove();
}

void TheoreticalBoard::instantiateBoard( Board *boardRef )
{
	std::vector<Piece *> *currVec = getPieceVec( pieceFromMove->getColor() );

	for ( unsigned int x = 0; x < currVec->size(); x++ )
	{
		if ( (*currVec->at( x )) == (*pieceFromMove) )
		{
			currVec->at( x ) = pieceFromMove;
			break;
		}
	}
	boardarr[pieceFromMove->getLoc().fy()][pieceFromMove->getLoc().fx()] = pieceFromMove;

	std::string temp = pieceAtMove->getColor();
	if ( temp == "None" )return;

	currVec = getPieceVec( temp );
	for ( unsigned int x = 0; x < currVec->size(); x++ )
	{
		if ( currVec->at( x ) == pieceAtMove )
		{
			currVec->at( x ) = pieceAtMove;
		}
	}
	
	boardarr[pieceAtMove->getLoc().fy()][pieceAtMove->getLoc().fx()] = pieceAtMove;
}

void TheoreticalBoard::doMove()
{
	//check for enpassant
	if ( didEnpassant )
	{
		//change the pieces
		int pos = 1 + ( -2 * ( activeTurn != "White" ) );
		didEnpassant = false;

		boardarr[move->ty() - pos][move->tx()]->capture();
		boardarr[move->ty() - pos][move->tx()] = emptySquare;
	}
	else
	{
		boardarr[move->ty()][move->tx()]->capture();
	}

	boardarr[move->ty()][move->tx()] = boardarr[move->fy()][move->fx()];
	boardarr[move->fy()][move->fx()] = emptySquare;
	boardarr[move->ty()][move->tx()]->moved();

	//check if pawn is at end of board
	if ( boardarr[move->tx()][move->ty()]->getType() == Piece::pawn && ( move->tx() == 7 || move->tx() == 0 ) )
	{
		boardarr[move->tx()][move->ty()]->setType( changePawn() );
	}

	//update location stored in piece class
	boardarr[move->ty()][move->tx()]->setLoc( *move );

	//change turn
	if ( activeTurn == "Black" )activeTurn = "White";
	else activeTurn = "Black";
}

bool TheoreticalBoard::KingIsInCheck()
{
	std::string t = "White";
	if ( activeTurn == t )t = "Black";

	std::vector<Location> oppMoves = getAllMoves( activeTurn );
	Location kingPtr = getKing(t)->getLoc();
	
	for ( unsigned int x = 0; x < oppMoves.size(); x++ )
	{
		if ( oppMoves.at( x ).tx() == kingPtr.fx() && oppMoves.at( x ).ty() == kingPtr.fy() )
			return true;
	}
	return false;
}

int TheoreticalBoard::rating( std::string turn )
{
	int whiteRating = getAllMoves( "White" ).size();
	int blackRating = getAllMoves( "Black" ).size();
	if ( turn == "White" )return whiteRating - blackRating;
	else return blackRating - whiteRating;
}


