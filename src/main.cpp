#include <iostream>
#include <fstream>
#include "../include/Raw_Julia.h"
//#include <cstdio>

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
    double left_up_I;
    double left_up_R;
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

int main() {
    data_julia arg;
    arg.width = 800;
    arg.height = 800;
    arg.step_R = 0.00125;
    arg.step_I = 0.00125;
    arg.left_up_R = -0.50;
    arg.left_up_I = -0.50;
    arg.radius = 40000000;
    //char image[2430000]; //300x300
    DIB dib = calc_DIB_and_padding(arg);
    //char dib[54] = {};
            std::cout << dib.RAW_SIZE;
    char * image= new char[dib.RAW_SIZE*4];

    std::fstream file;
    std::cout << "Size of DIB : " << sizeof(DIB) << '\n';
    //TODO: CALL
    std::cout << "result : " << gen_Julia(&arg, &image[0]) << '\n';

    file.open("../output.bmp", std::ios::out);
    file.write((char*)&dib, sizeof(dib));
    file.write(image, dib.RAW_SIZE*4); //sizeof(image));
    file.close();

    return 0;
}