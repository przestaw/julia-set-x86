#include <iostream>
#include <fstream>
#include "../include/Raw_Julia.h"
//#include <cstdio>

struct __attribute__((__packed__)) DIB{
    __uint16_t TYPE = 19778;
    __uint32_t FILE_SIZE = 0;/////
    __uint16_t R1 = 0;
    __uint16_t R2 = 0;
    __uint32_t OFFSET = 54;
    __uint32_t DIBSIZE = 40;
    __uint32_t width = 0;///
    __uint32_t height = 0;///
    __uint16_t planes = 1;
    __uint16_t BPP = 24;
    __uint32_t BI_RGB = 0;
    __uint32_t RAW_SIZE = 0;///
    __uint32_t RES_X = 0;
    __uint32_t RES_Y = 0;
    __uint32_t NO_COLOR = 0;
    __uint32_t IMPOR_COLOR = 0;
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
  u_int pad = (ret.width*3)%4;
  ret.RAW_SIZE = (ret.width + pad) * ret.height; //?? unnescesary
  ret.FILE_SIZE = ret.RAW_SIZE + ret.OFFSET;
  return ret;
}

int main() {
    data_julia arg;
    arg.width = 900;
    arg.height = 900;
    arg.step_R = 0.001;
    arg.step_I = 0.001;
    arg.left_up_R = -0.50;
    arg.left_up_I = -0.50;
    arg.radius = 40000000;
    //char image[2430000]; //300x300
    DIB dib = calc_DIB_and_padding(arg);
    //char dib[54] = {};
            std::cout << dib.RAW_SIZE;
    char * image= new char[dib.RAW_SIZE*3];
    std::fstream file;
    std::cout << "Size of argument : " << sizeof(arg) << '\n';
    //TODO: CALL
    std::cout << "result : " << gen_Julia(&arg, &image[0]) << '\n';
    std::cout << "Size of image : " << dib.RAW_SIZE*3/*sizeof(image)*/ << '\n';



    file.open("../output.bmp", std::ios::out);
    file.write((char*)&dib, 54);
    file.write(image, dib.RAW_SIZE*3); //sizeof(image));
    file.close();

    Raw_Julia julia_obj(10000, 10000);
    julia_obj.save_file("../test_obj.bmp");
    return 0;
}