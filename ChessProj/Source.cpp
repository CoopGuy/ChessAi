#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include "Board.h"

void doMove(Board &GameBoard)
{
	////Take initial move input
	//std::string move;
	//std::string temp;

	//std::cout << "Location of piece to move: ";
	//std::cin >> temp;
	//move = temp;

	//std::cout << "Location to move to: ";
	//std::cin >> temp;
	//move = move + temp;

	//while ( !GameBoard.validityTest( move ) )//If move is invalid input again
	//{
	//	std::cout << "Move is invalid. Try again." << std::endl;
	//	std::cout << "Location of piece to move: ";
	//	std::cin >> temp;
	//	move = temp;

	//	std::cout << "Location to move to: ";
	//	std::cin >> temp;
	//	move = move + temp;
	//}

	//GameBoard.doMove( move );
}

int main()
{

	Board GameBoard = Board();
	GameBoard.printBoard();

	while ( !GameBoard.ended() )//start game loop
	{
		std::cout << "Its " << GameBoard.turn() << "'s move" << std::endl;

		//Function for getting and playing move
		//Includes err checking for invalid moves

		{
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
		}
		//Prints board after every turn
		GameBoard.printBoard();
	}

	GameBoard.printBoard();
}