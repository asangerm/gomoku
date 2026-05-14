#include <SFML/Graphics.hpp>
#include "../include/Game.hpp"
#include <iostream>

const int CELL_SIZE = 40;
const int OFFSET = 50;
const int WIN_SIZE = (BOARD_SIZE - 1) * CELL_SIZE + 2 * OFFSET;
const int STONE_SIZE = 16;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIN_SIZE, WIN_SIZE), "Gomoku");

    Game game;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                int x = (mouseX - OFFSET + CELL_SIZE / 2) / CELL_SIZE;
                int y = (mouseY - OFFSET + CELL_SIZE / 2) / CELL_SIZE;

                if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
                {
                    if (game.makeMove(x, y))
                    {
                        if (game.gameOver)
                        {
                            std::cout << "Game Over! ";
                            if (game.winner == BLACK)
                                std::cout << "Black wins!" << std::endl;
                            else
                                std::cout << "White wins!" << std::endl;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color(210, 180, 140));

        // grille
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            sf::Vertex horizontal[] =
            {
                sf::Vertex(sf::Vector2f(OFFSET, OFFSET + i * CELL_SIZE)),
                sf::Vertex(sf::Vector2f(OFFSET + (BOARD_SIZE - 1) * CELL_SIZE, OFFSET + i * CELL_SIZE))
            };

            sf::Vertex vertical[] =
            {
                sf::Vertex(sf::Vector2f(OFFSET + i * CELL_SIZE, OFFSET)),
                sf::Vertex(sf::Vector2f(OFFSET + i * CELL_SIZE, OFFSET + (BOARD_SIZE - 1) * CELL_SIZE))
            };

            window.draw(horizontal, 2, sf::Lines);
            window.draw(vertical, 2, sf::Lines);
        }

        // pierres
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            for (int y = 0; y < BOARD_SIZE; y++)
            {
                if (game.board.grid[x][y] != EMPTY)
                {
                    sf::CircleShape stone(STONE_SIZE);
                    stone.setPosition(OFFSET + x * CELL_SIZE - STONE_SIZE, OFFSET + y * CELL_SIZE - STONE_SIZE);

                    if (game.board.grid[x][y] == BLACK)
                        stone.setFillColor(sf::Color::Black);
                    else
                        stone.setFillColor(sf::Color::White);

                    window.draw(stone);
                }
            }
        }

        // Afficher les captures
        sf::Font font; // À charger depuis un fichier si disponible
		if (!font.loadFromFile("assets/ARIAL.TTF"))
			return 1;

		sf::Text turnText;
		turnText.setFont(font);
		turnText.setCharacterSize(20);
		turnText.setFillColor(sf::Color::Black);
		turnText.setPosition(50, 20);
		if (game.currentPlayer == BLACK)
			turnText.setString("Aux noirs de jouer");
		else
			turnText.setString("Aux blancs de jouer");
		window.draw(turnText);

		sf::Text captureText;
		captureText.setFont(font);
        captureText.setCharacterSize(20);
        captureText.setFillColor(sf::Color::Black);
        std::string captureStr = "Black: " + std::to_string(game.blackCaptures) + 
                                " | White: " + std::to_string(game.whiteCaptures);
        captureText.setString(captureStr);
        captureText.setPosition(50, WIN_SIZE - 40);
        window.draw(captureText);

        window.display();
    }

    return 0;
}