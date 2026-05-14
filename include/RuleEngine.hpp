#pragma once

#include "Board.hpp"

class RuleEngine
{
	public:
		// Détection de victoire par alignement (5 ou plus)
		bool checkWinByAlignment(const Board& board, int x, int y, int player);
		
		// Détection de victoire par capture (10 paires)
		bool checkWinByCapture(int captureCount);
		
		// Vérification et exécution des captures
		int performCaptures(Board& board, int x, int y, int player);
		
		// Vérification des double-trois
		bool isDoubleThreat(const Board& board, int x, int y, int player);

	private:
		// Comptage de pierres alignées dans une direction
		int countDirection(const Board& board, int x, int y, int player, int dx, int dy);
		
		// Vérification d'une libre-trois dans une direction
		bool isFreeThree(const Board& board, int x, int y, int player, int dx, int dy);
		
		// Vérification d'une paire encadrée à une position donnée
		bool checkPairCapture(const Board& board, int x, int y, int dx, int dy, int player);
	};