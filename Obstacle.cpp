#include "Obstacle.h"

Obstacle::Obstacle(float x, float y, const sf::Texture& texture, int tileSize) {
    sprite.setTexture(texture);
    sprite.setPosition(x * tileSize, y * tileSize);
    // Set the scale of the sprite to match the tileSize
    sprite.setScale(tileSize / static_cast<float>(texture.getSize().x), tileSize / static_cast<float>(texture.getSize().y));
}

void Obstacle::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Obstacle::getBounds() {
    return sprite.getGlobalBounds();
}

void Obstacle::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

