#include "Constsants.hpp"

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, WIDTH), "SmashStoneGUI", sf::Style::Titlebar | sf::Style::Close);

    // Board
    sf::Texture board_Tex;
    if (!board_Tex.loadFromFile("Resource/board.png"))
    {
        return -1;
    }

    sf::Sprite board_Sprite;
    board_Sprite.setTexture(board_Tex);
    auto rect = board_Sprite.getTextureRect();
    board_Sprite.scale(sf::Vector2f(
		static_cast<float>(WIDTH) / rect.width,
		static_cast<float>(HEIGHT) / rect.height
	));

	sf::CircleShape circle(41.574803f * RESCALE_FACTOR);
    circle.setFillColor(sf::Color::Black);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(board_Sprite);
        window.draw(circle);
        window.display();
    }

    return 0;
}
