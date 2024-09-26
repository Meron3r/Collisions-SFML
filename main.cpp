#include <SFML/Graphics.hpp>

sf::RenderWindow window(sf::VideoMode(1200, 800), "Simple AABB Collision");
sf::RectangleShape player, square;
sf::Clock deltaclock;
float px, py, sqx, sqy; float speed; float dt;

bool colliding(sf::RectangleShape a, sf::RectangleShape b)
{
    if (a.getGlobalBounds().intersects(b.getGlobalBounds()))
        return true;
    else
        return false;
}

void borders()
{
    if (px < 0) px = 0;
    if (py < 0) py = 0;
    if (px + 50 > 1200) px = 1200 - 50;
    if (py + 50 > 800) py = 800 - 50;
}

void changePxPy(float chx, float chy)
{
    px += chx * dt; py += chy * dt;
    player.setPosition(px, py);
}

void keyMapping()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        changePxPy(0, -speed);
    if (colliding(player, square))
        changePxPy(0, speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        changePxPy(0, speed);
    if (colliding(player, square))
        changePxPy(0, -speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        changePxPy(-speed, 0);
    if (colliding(player, square))
        changePxPy(speed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        changePxPy(speed, 0);
    if (colliding(player, square))
        changePxPy(-speed, 0);

    borders();
}

void init()
{
    px = py = 0; sqx = 700; sqy = 500;
    speed = 400;

    player.setSize(sf::Vector2f(50, 50));
    player.setFillColor(sf::Color::White);
    player.setPosition(px, py);
    
    square.setSize(sf::Vector2f(50, 50));
    square.setFillColor(sf::Color::Red);
    square.setPosition(sqx, sqy);
}

void update()
{
    player.setPosition(px, py);
}

void render()
{
    window.draw(player);
    window.draw(square);
}

int main()
{
    init();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        sf::Time temp = deltaclock.restart();
        dt = temp.asSeconds();

        keyMapping();
        update();

        window.clear(sf::Color::Black);
        render();
        window.display();
    }

    return 0;
}
