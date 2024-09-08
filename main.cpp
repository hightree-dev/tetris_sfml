#include "Block.hpp"
#include "Board.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

/*
0 1
2 3
4 5
6 7
*/

std::vector<std::array<int, 4>> figures = {
  { 0, 1, 3, 5 },
  { 0, 1, 2, 3 },
  { 1, 3, 2, 5 },
  { 1, 3, 5, 7 }
};
std::vector<sf::Color> colors = {
  sf::Color::Red,
  sf::Color::Green,
  sf::Color::Blue,
  sf::Color::Yellow,
  sf::Color::Cyan,
  sf::Color::Magenta
};

int main()
{
  std::srand(std::time(0));

  Board board(10, 20);
  Block block(figures[std::rand() % figures.size()], colors[std::rand() % colors.size()]);

  int score = 0;
  float timer = 0.f;
  float delay = 0.5f;

  sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");
  
  sf::Font font;
  font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf");
  
  sf::Text scoreText;
  scoreText.setFont(font);
  scoreText.setCharacterSize(20);
  scoreText.setString("Score : " + std::to_string(score));
  scoreText.setFillColor(sf::Color::Black);
  scoreText.setPosition(210, 10);

  sf::Clock clock;

  while (window.isOpen())
  {
    
    timer += clock.getElapsedTime().asSeconds();
    clock.restart();

    sf::Event event;
    while (window.pollEvent(event))
    {
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Left) block.move({-1.f, 0.f});
        else if (event.key.code == sf::Keyboard::Right) block.move({1.f, 0.f});
        else if (event.key.code == sf::Keyboard::Up) block.rotate();
        else if (event.key.code == sf::Keyboard::Down) delay = 0.05f;
        if (board.isCollision(block.getPosisitons()))
          block.back();
        break;
      default:
        break;
      }
    }

    if (timer > delay)
    {
      block.move({0.f, 1.f});
      if (board.isCollision(block.getPosisitons()))
      {
        block.back();
        if (board.isCollision(block.getPosisitons()))
        {
          // Todo Game Over
        }
        else 
        {
          for (const auto& pos : block.getPosisitons())
            board.setColor(pos.x, pos.y, block.getColor());
          int clearedLineCount = board.clearLine();
          score += clearedLineCount;
          scoreText.setString("Score : " + std::to_string(score));
          block = Block(figures[std::rand() % figures.size()], colors[std::rand() % colors.size()]);
        } 
      }
          
      timer = 0.f;
      delay = 0.5f;
    }
    
    window.clear(sf::Color::White);
    board.draw(window);
    block.draw(window);
    window.draw(scoreText);
    window.display();
  }
}