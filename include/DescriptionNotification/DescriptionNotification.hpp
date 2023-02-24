#ifndef DESCRIPTION_NOTIFICATION_HPP
#define DESCRIPTION_NOTIFICATION_HPP
#include "../include.hpp"

class DescriptionNotification{
    sf::RectangleShape mainShape;
    sf::Text text;

    void init();
    void initShape();

public:
    DescriptionNotification(const sf::Vector2f&, const std::string&);
    ~DescriptionNotification();

public:

    void update();
    void render(sf::RenderTarget*);

    const bool visible() const;
};

#endif