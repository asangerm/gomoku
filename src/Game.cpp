#include "../include/Game.hpp"

Game::Game()
    : currentPlayer(BLACK), blackCaptures(0), whiteCaptures(0), gameOver(false), winner(EMPTY)
{
}

void Game::switchPlayer()
{
    currentPlayer = (currentPlayer == BLACK) ? WHITE : BLACK;
}

bool Game::makeMove(int x, int y)
{
    if (gameOver)
        return false;
    
    // Vérifier que la case est vide
    if (!board.placeStone(x, y, currentPlayer))
        return false;
    
    // Vérifier les captures
    int capturesThisTurn = ruleEngine.performCaptures(board, x, y, currentPlayer);
    
    if (currentPlayer == BLACK)
        blackCaptures += capturesThisTurn;
    else
        whiteCaptures += capturesThisTurn;
    
    // Vérifier victoire par capture (10 paires)
    if (ruleEngine.checkWinByCapture(blackCaptures) || ruleEngine.checkWinByCapture(whiteCaptures))
    {
        gameOver = true;
        winner = ruleEngine.checkWinByCapture(blackCaptures) ? BLACK : WHITE;
        return true;
    }
    
    // Vérifier victoire par alignement (mais seulement si pas de capture possible)
    if (ruleEngine.checkWinByAlignment(board, x, y, currentPlayer))
    {
        gameOver = true;
        winner = currentPlayer;
        return true;
    }
    
    // Vérifier double-trois (coup invalide)
    if (ruleEngine.isDoubleThreat(board, x, y, currentPlayer))
    {
        // Annuler le coup
        board.grid[x][y] = EMPTY;
        return false;
    }
    
    switchPlayer();
    return true;
}