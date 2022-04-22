#pragma once
#include "Piece.h"
#include "Location.h"


#include <iostream>
#include <string>
#include <vector>


class Board
{
	protected:
	Piece* boardarr[8][8];
	std::vector<Piece*> whitePieces;
	std::vector<Piece*> blackPieces;

	bool gameEnded;
	std::string activeTurn;
	bool check;
	Location pawnThatMoved;
	bool didEnpassant = false;
	Piece *emptySquare;

	public:

	//constructor
	Board();
	Board( const Board &Obj );
	void setVals();//constructor helper

	//Getters
	std::vector<Piece*> *getPieceVec( std::string str )
	{
		if ( str == "White" )return &whitePieces;
		else return &blackPieces;
	}
	bool ended() const { return gameEnded; };
	std::string turn() const { return activeTurn; };
	Location pawnMove() { return pawnThatMoved; };
	Piece *pieceAtLocation( Location &var, bool tf );

	//Print
	void printBoard() const;


	//Move related behavior
	bool checkMove( Location &l );
	bool validityTest( std::string move );
	void doMove( std::string move, bool needsTest = false );
	Piece::pieceType changePawn();

	std::vector<Location> getAllMoves( std::string turn );

	//Player Interface related functions 
	bool static parse( std::string move, Location &location );
	static int conv( char a );
	
};
