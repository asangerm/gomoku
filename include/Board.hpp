#pragma once

const int BOARD_SIZE = 19;

enum Cell
{
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

class Board
{
	public:
    	int grid[BOARD_SIZE][BOARD_SIZE];

		Board();

		bool placeStone(int x, int y, int player);
};