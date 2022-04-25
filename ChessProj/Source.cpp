#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include "Board.h"

int main()
{
	srand( time( NULL ) );
	Board GameBoard = Board();
	GameBoard.printBoard();

	while ( !GameBoard.ended() )//start game loop
	{
		std::cout << "Its " << GameBoard.turn() << "'s move" << std::endl;

		//Function for getting and playing move
		//Includes err checking for invalid moves

		//Take initial move input
		std::string move;
		std::string temp;

		std::cout << "Location of piece to move: ";
		std::cin >> temp;
		move = temp;

		std::cout << "Location to move to: ";
		std::cin >> temp;
		move = move + temp;

		while ( !GameBoard.validityTest( move ) )//If move is invalid input again
		{
			std::cout << "Move is invalid. Try again." << std::endl;
			std::cout << "Location of piece to move: ";
			std::cin >> temp;
			move = temp;

			std::cout << "Location to move to: ";
			std::cin >> temp;
			move = move + temp;
		}
		GameBoard.doMove( move );

		std::cout << "The Ai will now move\n";

		std::vector<Location> t = GameBoard.getAllMoves();
		bool a = GameBoard.doMove( t.at( rand() % t.size() ), true );
		while ( !a )
		{
			a = GameBoard.doMove( t.at( rand() % t.size() ), true );
		}

		//Prints board after every turn
		GameBoard.printBoard();

	}

	GameBoard.printBoard();
	std::cout << GameBoard.getResult();
}