#include <iostream>
#include <fstream>
#include "../include/Raw_Julia.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

int main()
{
  u_int width = 800, height = 800;
  double left = -2.0, right = 2.0, top = 2.0, bottom = -2.0;
  bool set_changed = true;
  Raw_Julia julia(800, 800);
  sf::RenderWindow window(sf::VideoMode(width, height), "Julia set generator x86-64");
  window.setVerticalSyncEnabled(true);
  window.setKeyRepeatEnabled(false);
  u_int8_t data[800][800][4] = {};
  sf::Image image;
  sf::Texture texture;
  //sf::Sprite canvas;
  //julia.set_square(right, left, top, bottom);
  //julia.use_julia(&data[0][0][0]);
  //image.create(width, height, &data[0][0][0]);
  //texture.loadFromImage(image);
  //canvas.setTexture(texture);

  double Re_res, Im_res;

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed){
        window.close();
      }else if (event.type == sf::Event::Resized) {
        width = window.getSize().x;
        height = window.getSize().y;
      }
    }

    Re_res = right - left;
    Im_res = top - bottom;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      left += 0.03*Re_res;
      right += 0.03*Re_res;
      set_changed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      left -= 0.03*Re_res;
      right -= 0.03*Re_res;
      set_changed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      top += 0.03*Im_res;
      bottom += 0.03*Im_res;
      set_changed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      top -= 0.03*Im_res;
      bottom -= 0.03*Im_res;
      set_changed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      top -= 0.05*Im_res;
      bottom += 0.05*Im_res;
      left += 0.05*Re_res;
      right -= 0.05*Re_res;
      set_changed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      top += 0.05*Im_res;
      bottom -= 0.05*Im_res;
      left -= 0.05*Re_res;
      right += 0.05*Re_res;
      set_changed = true;
    }

    //window.clear();
    if(set_changed){
      sf::Sprite new_sprite;
      julia.set_square(right, left, top, bottom);
      julia.use_julia(&data[0][0][0]);
      image.create(width, height, &data[0][0][0]);
      texture.loadFromImage(image);
      new_sprite.setTexture(texture);
      set_changed = false;
      window.draw(new_sprite);
    }
    window.display();
  }

  return 0;
}