#include <iostream>
#include <fstream>
#include "../include/Raw_Julia.h"
//#include <cstdio>
/*
struct __attribute__((__packed__)) DIB{
    __uint16_t TYPE = 19778;
    __uint32_t FILE_SIZE = 0;/////
    __uint16_t R1 = 0;
    __uint16_t R2 = 0;
    __uint32_t OFFSET = 122;
    __uint32_t DIBSIZE = 108;
    __uint32_t width = 0;///
    __uint32_t height = 0;///
    __uint16_t planes = 1;
    __uint16_t BPP = 32;
    __uint32_t BI_RGB = 3;
    __uint32_t RAW_SIZE = 0;///
    __uint32_t RES_X = 0;
    __uint32_t RES_Y = 0;
    __uint32_t NO_COLOR = 0;
    __uint32_t IMPOR_COLOR = 0;
    __uint32_t RED_MASK = 0x000000ff;
    __uint32_t GREEN_MASK = 0xff000000;
    __uint32_t BLUE_MASK = 0x00ff0000;
    __uint32_t ALPHA_MASK = 0x00000000;
    __uint32_t LCS_COLOR_SPACE = 0x206e6957;//0x73524742;
    //__uint8_t unused[24] = {};
    __uint16_t here_unused[25] = {};
};

struct __attribute__((aligned(32))) data_julia
{
    __int64_t width;
    __int64_t height;
    double step_I;
    double step_R;
    double left_down_I;
    double left_down_R;
    double radius;
};

extern "C"
{
  int gen_Julia(data_julia *argument, char *array);
}

DIB calc_DIB_and_padding(data_julia &data)
{
  DIB ret;
  ret.height = data.height;
  ret.width = data.width;
  ret.RAW_SIZE = ret.width * ret.height; //?? unnescesary
  ret.FILE_SIZE = ret.RAW_SIZE*4 + ret.OFFSET;
  return ret;
}
*/
int main()
{
  auto u_int_input = []{
      u_int a;
      while(!(std::cin >> a))
      {
        std::cin.clear();
        std::cin.sync();
        std::cin.ignore(100, '\n');
        std::cout << "Wrong input\n";
      }
      return a;
  };
  auto double_input = [] {
      double a;
      while (!(std::cin >> a)) {
        std::cin.clear();
        std::cin.sync();
        std::cin.ignore(100, '\n');
        std::cout << "Wrong input\n";
      }
      return a;
  };
  auto string_input = []{
      std::string a;
      while(!(std::cin >> a))
      {
        std::cin.clear();
        std::cin.sync();
        std::cin.ignore(100, '\n');
        std::cout << "Wrong input\n";
      }
      return a;
  };

  std::string name = "output.bmp";
  u_int width, height;
  double top, bottom, left, right;
  Raw_Julia julia(0, 0);
  do{
    std::cout << "Enter desired width : ";
    width = u_int_input();
    std::cout << "Enter desired height : ";
    height = u_int_input();
    std::cout << "Enter desired top imaginary bound : ";
    top = double_input();
    std::cout << "Enter desired bottom imaginary bound : ";
    bottom = double_input();
    std::cout << "Enter desired right real bound : ";
    right = double_input();
    std::cout << "Enter desired left real bound : ";
    left = double_input();
    std::cout << "Enter desired filename with *.bmp extension";
    name = string_input();
    name = "../" + name;
    julia.set_size(width, height);
    julia.set_square(right, left, top, bottom);
    julia.save_file(name);
    std::cout << "Press 0 to generate another one\n";
  }while(0);

  return 0;
}