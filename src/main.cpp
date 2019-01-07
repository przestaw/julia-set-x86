#include <iostream>
#include <fstream>
#include "../include/Raw_Julia.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <sstream>

int main()
{
  u_int width = 600, height = 400, depth = 63;
  double left = -3.0, right = 3.0, top = 2.0, bottom = -2.0;
  double Re_res, Im_res, Re = 0.0, Im = 1.0;
  bool set_changed = true;
  Raw_Julia julia(width, height);
  julia.set_depth(depth);
  sf::RenderWindow window(sf::VideoMode(width, height), "Julia set generator x86-64");
  window.setVerticalSyncEnabled(true);
  window.setKeyRepeatEnabled(false);
  //u_int8_t data[800][800][4] = {};
  u_int8_t *data = new u_int8_t[width*height*4];
  sf::Text label;
  sf::Font font;
  sf::Image image;
  sf::Texture texture;

  if(!font.loadFromFile("good-times.ttf"))
  {
    return -99;
  }

  label.setFont(font);
  label.setColor(sf::Color::White);
  label.setCharacterSize(14);
  //label.setString(my_stream.str());
  //my_stream.clear();

  //sf::Sprite canvas;
  //julia.set_square(right, left, top, bottom);
  //julia.use_julia(&data[0][0][0]);
  //image.create(width, height, &data[0][0][0]);
  //texture.loadFromImage(image);
  //canvas.setTexture(texture);

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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      left += 0.03*Re_res;
      right += 0.03*Re_res;
      set_changed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      left -= 0.03*Re_res;
      right -= 0.03*Re_res;
      set_changed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      top += 0.03*Im_res;
      bottom += 0.03*Im_res;
      set_changed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
      Re -= 0.005;
      set_changed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
      Re += 0.005;
      set_changed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
      Im -= 0.005;
      set_changed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
      Im += 0.005;
      set_changed = true;
    }

    //window.clear();
    if(set_changed){
      std::stringstream my_stream;
      my_stream << "Window Re[" << left << ","<< right <<"] x Im[" << bottom << ", " << top << "]\nConst : [Re : " << Re << " , Im : " << Im<< " ], \nDepth : " << depth;
      label.setString(my_stream.str());
      sf::Sprite new_sprite;
      julia.set_square(right, left, top, bottom);
      julia.set_Z_constant(Re, Im);
      julia.use_julia(data);
      image.create(width, height, data);
      texture.loadFromImage(image);
      new_sprite.setTexture(texture);
      set_changed = false;

      window.draw(new_sprite);
      window.draw(label);
    }

    window.display();
  }

  delete[] data;
  return 0;
}