#include "../include/Game.hpp"

Game::Game()
{
    currentPlayer = BLACK;
}

void Game::switchPlayer()
{
    currentPlayer = (currentPlayer == BLACK) ? WHITE : BLACK;
}