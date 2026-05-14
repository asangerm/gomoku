#pragma once

#include "Board.hpp"
#include "RuleEngine.hpp"

class Game
{
	public:
		Board board;
		RuleEngine ruleEngine;
		int currentPlayer;
		
		int blackCaptures;
		int whiteCaptures;
		
		bool gameOver;
		int winner; // BLACK, WHITE, ou EMPTY si pas de gagnant
		
		Game();
		
		void switchPlayer();
		
		// Valide et exécute un coup
		bool makeMove(int x, int y);
};