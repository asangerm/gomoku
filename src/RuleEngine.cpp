#include "../include/RuleEngine.hpp"
#include <string>
#include <vector>

// Vérifie si le joueur a gagné avec 5+ pierres alignées
bool RuleEngine::checkWinByAlignment(const Board& board, int x, int y, int player)
{
    // 4 directions: horizontal, vertical, diagonale \, diagonale /
    int directions[4][2] =
	{
        {1, 0},   // horizontal
        {0, 1},   // vertical
        {1, 1},   // diagonale 1
        {1, -1}   // diagonale 2
    };
    
    for (int i = 0; i < 4; i++)
    {
        int dx = directions[i][0];
        int dy = directions[i][1];
        
        // Compter dans les deux sens
        int count = 1; // la pierre placée
        
        // Compter vers la direction positive
        count += countDirection(board, x, y, player, dx, dy);
        
        // Compter vers la direction négative
        count += countDirection(board, x, y, player, -dx, -dy);
        
        if (count >= 5)
            return true;
    }
    
    return false;
}

// Compte les pierres alignées dans une direction
int RuleEngine::countDirection(const Board& board, int x, int y, int player, int dx, int dy)
{
    int count = 0;
    int nx = x + dx;
    int ny = y + dy;
    
    while (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE)
    {
        if (board.grid[nx][ny] == player)
        {
            count++;
            nx += dx;
            ny += dy;
        }
        else
            break;
    }
    
    return count;
}

// Vérifie si le joueur a gagné avec 10 paires capturées
bool RuleEngine::checkWinByCapture(int captureCount)
{
    return captureCount >= 10;
}

// Effectue les captures après un placement de pierre
int RuleEngine::performCaptures(Board& board, int x, int y, int player)
{
    int capturesCount = 0;
    //int opponent = (player == BLACK) ? WHITE : BLACK;
    
    // 4 directions pour vérifier les captures
    int directions[4][2] =
	{
        {1, 0},   // horizontal
        {0, 1},   // vertical
        {1, 1},   // diagonale 1
        {1, -1}   // diagonale 2
    };
    
    for (int i = 0; i < 4; i++)
    {
        int dx = directions[i][0];
        int dy = directions[i][1];
        
        // Vérifier capture dans les deux sens
        if (checkPairCapture(board, x, y, dx, dy, player))
        {
            // Capturer la paire
            int capX = x + dx;
            int capY = y + dy;
            board.grid[capX][capY] = EMPTY;
            
            int capX2 = x + 2 * dx;
            int capY2 = y + 2 * dy;
            board.grid[capX2][capY2] = EMPTY;
            
            capturesCount++;
        }
        
        if (checkPairCapture(board, x, y, -dx, -dy, player))
        {
            // Capturer la paire
            int capX = x - dx;
            int capY = y - dy;
            board.grid[capX][capY] = EMPTY;
            
            int capX2 = x - 2 * dx;
            int capY2 = y - 2 * dy;
            board.grid[capX2][capY2] = EMPTY;
            
            capturesCount++;
        }
    }
    
    return capturesCount;
}

// Vérifie si une paire peut être capturée dans une direction donnée
bool RuleEngine::checkPairCapture(const Board& board, int x, int y, int dx, int dy, int player)
{
    int opponent = (player == BLACK) ? WHITE : BLACK;
    
    // Vérifier: [player][opponent][opponent][player]
    // Position actuelle: x, y (contient player)
    // Positions à vérifier: x+dx, y+dy et x+2*dx, y+2*dy doivent être opponent
    // Position de fermeture: x+3*dx, y+3*dy doit être player
    
    int pos1X = x + dx;
    int pos1Y = y + dy;
    int pos2X = x + 2 * dx;
    int pos2Y = y + 2 * dy;
    int pos3X = x + 3 * dx;
    int pos3Y = y + 3 * dy;
    
    // Vérifier limites
    if (pos1X < 0 || pos1X >= BOARD_SIZE || pos1Y < 0 || pos1Y >= BOARD_SIZE)
        return false;
    if (pos2X < 0 || pos2X >= BOARD_SIZE || pos2Y < 0 || pos2Y >= BOARD_SIZE)
        return false;
    if (pos3X < 0 || pos3X >= BOARD_SIZE || pos3Y < 0 || pos3Y >= BOARD_SIZE)
        return false;
    
    // Vérifier le pattern: player-opponent-opponent-player
    return board.grid[pos1X][pos1Y] == opponent &&
           board.grid[pos2X][pos2Y] == opponent &&
           board.grid[pos3X][pos3Y] == player;
}

// Détecte les double-trois
bool RuleEngine::isDoubleThreat(const Board& board, int x, int y, int player)
{
    int freeThreeCount = 0;
    
    // 4 directions à vérifier
    int directions[4][2] =
	{
        {1, 0},   // horizontal
        {0, 1},   // vertical
        {1, 1},   // diagonale 1
        {1, -1}   // diagonale 2
    };
    
    for (int i = 0; i < 4; i++)
    {
        if (isFreeThree(board, x, y, player, directions[i][0], directions[i][1]))
            freeThreeCount++;
    }
    
    // Double-trois si 2 ou plus de libres-trois
    return freeThreeCount >= 2;
}

bool RuleEngine::isFreeThree(const Board& board, int x, int y, int player, int dx, int dy)
{
    std::string line;

    // Construire une ligne de 9 cases centrée sur le coup
    for (int i = -4; i <= 4; i++)
    {
        int nx = x + i * dx;
        int ny = y + i * dy;

        if (nx < 0 || nx >= BOARD_SIZE ||
            ny < 0 || ny >= BOARD_SIZE)
        {
            line += 'X'; // bord = bloqué
        }
        else if (nx == x && ny == y)
        {
            line += 'B'; // pierre simulée
        }
        else if (board.grid[nx][ny] == EMPTY)
        {
            line += '.';
        }
        else if (board.grid[nx][ny] == player)
        {
            line += 'B';
        }
        else
        {
            line += 'X'; // adversaire
        }
    }

    // Patterns classiques de free-three
    static const std::vector<std::string> patterns =
    {
        ".BBB.",
        ".BB.B.",
        ".B.BB.",
        "..BBB..",
        ".B.B.B."
    };

    for (const auto& pattern : patterns)
    {
        if (line.find(pattern) != std::string::npos)
            return true;
    }

    return false;
}