#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

void moveInDirection(const sf::Time &elapsed, const sf::Keyboard::Key &key,  sf::Sprite &guy)
{
    int speed_x = 250;
    int speed_y = 250;


    sf::FloatRect guybounds = guy.getGlobalBounds();
    if(key == sf::Keyboard::Up && !(guybounds.top <= 0.0))
    {
        guy.move(0, -speed_y * elapsed.asSeconds());
    }
    else if(key == sf::Keyboard::Right && !(guybounds.left >= 800 - guybounds.width))
    {
        guy.move(speed_x * elapsed.asSeconds(), 0);
    }
    else if(key == sf::Keyboard::Down && !(guybounds.top >= 600 - guybounds.height))
    {
        guy.move(0, speed_y * elapsed.asSeconds());
    }
    else if(key == sf::Keyboard::Left && !(guybounds.left <= 0.0))
    {
        guy.move(-speed_x * elapsed.asSeconds(), 0);
    }
}


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");


    // create textures
    sf::Texture textureguy;
    if(!textureguy.loadFromFile("guy.png")) { return 1; }
    sf::Texture texturewall;
    if(!texturewall.loadFromFile("wall.png")) { return 1; }
    sf::Texture texturegrass;
    if(!texturegrass.loadFromFile("grass.png")) { return 1; }

    // create sprites
    // grass background
    texturegrass.setRepeated(true);
    sf::Sprite grass;
    grass.setTexture(texturegrass);
    grass.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
//    grass.setScale(float(texturegrass.getSize().x) / float(window.getSize().x), float(texturegrass.getSize().y) / float(window.getSize().y));
    // guy
    sf::Sprite guy;
    guy.setTexture(textureguy);
    // walls
    texturewall.setRepeated(true);
    std::vector<sf::Sprite> walls;
    sf::Sprite wall;
    wall.setTexture(texturewall);
    // Vertical wall
    wall.setTextureRect(sf::IntRect(0, 0, 50, 150));
    wall.setPosition(100, 100);
    walls.emplace_back(wall);
    // Horizontal wall
    wall.setTextureRect(sf::IntRect(0, 0, 150, 50));
    wall.setPosition(300, 300);
    walls.emplace_back(wall);

    sf::Clock clock;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            moveInDirection(elapsed, sf::Keyboard::Up, guy);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            moveInDirection(elapsed, sf::Keyboard::Down, guy);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            moveInDirection(elapsed, sf::Keyboard::Left, guy);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            moveInDirection(elapsed, sf::Keyboard::Right, guy);
        }

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // quit by pressing Q
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                return 0;
            }
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(grass);
        for(auto &wall : walls)
        {
            window.draw(wall);
        }
        window.draw(guy);
        // end the current frame
        window.display();
    }

    std::cout << "\nDone!!\n\n";

    return 0;
}
