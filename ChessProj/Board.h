#pragma once
#include "Piece.h"
#include <iostream>
#include <string>
#include "Location.h"
#include <vector>


class Board
{
	private:

	Piece boardarr[8][8];

	bool gameEnded;
	std::string activeTurn;
	Location pawnThatMoved;
	bool check;
	bool enpassant;

	bool checkPawn( Location &l );
	bool checkKnight( Location &l );
	bool checkBishop( Location &l );
	bool checkRook( Location &l );
	bool checkQueen( Location &l );
	bool checkKing( Location &l );

	public:

	//constructor
	Board();

	void setVals();//constructor helper


	//Getters
	bool ended() const { return gameEnded; };
	std::string turn() const { return activeTurn; };

	//"Getter"
	void printBoard() const;


	//Useful Behavior
	
	bool validityTest( std::string move );
	void doMove( std::string move, bool needsTest = false );
	
	bool static parse( std::string move, Location &location );
	static int conv( char a );
	Piece *pieceAtLocation( Location &var, bool tf );

	Piece::pieceType changePawn();

	bool checkDiagonal( Location loc );
	bool checkLinear( Location loc );

	std::vector<Location> getPossibleDiagsFromPos( Location &loc, int lim = 8 );
	std::vector<Location> getPossibleLinearsFromPos( Location &loc, int lim = 8);
	bool moveInList( Location &l, std::vector<Location> list ) const;
};