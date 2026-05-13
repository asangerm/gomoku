#include "../include/Board.hpp"

Board::Board()
{
    for (int x = 0; x < BOARD_SIZE; x++)
	{
        for (int y = 0; y < BOARD_SIZE; y++)
		{
            grid[x][y] = EMPTY;
        }
    }
}

bool Board::placeStone(int x, int y, int player)
{
    if (grid[x][y] != EMPTY)
        return false;

    grid[x][y] = player;
    return true;
}