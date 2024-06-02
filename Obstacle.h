#pragma once
#include <SFML/Graphics.hpp>

class Obstacle {
public:
    Obstacle(float x, float y, const sf::Texture& texture, int tileSize);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds();
    void draw(sf::RenderWindow& window) const;


private:
    sf::Sprite sprite;
};