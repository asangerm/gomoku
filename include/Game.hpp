#pragma once

#include "Board.hpp"

class Game
{
	public:
		Board board;
		int currentPlayer;

		Game();

		void switchPlayer();
};