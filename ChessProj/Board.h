#pragma once
#include "Piece.h"
#include <iostream>
#include <string>
#include "Location.h"


class Board
{
	private:

	Piece boardarr[8][8];
	bool gameEnded;
	std::string activeTurn;
	bool pawnMoved2;
	bool check;

	bool checkPawn( Location location, std::string activeTurn );
	bool checkKnight( Location location );
	bool checkBishop( Location location );
	bool checkRook( Location location );
	bool checkQueen( Location location );
	bool checkKing( Location location );

	public:

	//constructor
	Board();

	void setVals();//constructor helper


	//Getters
	bool ended() const { return gameEnded; };
	std::string turn() const { return activeTurn; };

	//"Getter"
	void printBoard();


	//Useful Behavior
	bool validityTest( std::string move );
	void doMove( std::string move, bool needsTest = false );
	bool static parse( std::string move, Location &location );
	Piece::pieceType changePawn();
	static int conv( char a );
	bool checkDiagonal( Location loc );
	bool checkLinear( Location loc );

};