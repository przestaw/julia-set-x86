#include <iostream>
#include <fstream>
//#include <cstdio>

struct data_julia
{
    __int64_t width;
    __int64_t height;
    double left_down_R;
    double left_down_I;
    double right_up_R;
    double right_up_I;
};

char output_str[256];
char input[256];

extern "C"
{
  int func(data_julia *argument, char *array);
}

int main() {
    data_julia arg;
    arg.width = 300;
    arg.height = 300;
    arg.left_down_R = -1.5;
    arg.left_down_I = -1.5;
    arg.right_up_R = 1.5;
    arg.right_up_I = 1.5;
    char image[270000] = {}; //300x300
    char dib[54] = {};
    std::fstream file;
    file.open("../hed.mine", std::ios::in);//BMP 300x300 RGB uncompressed header
    file.read(dib, 54);
    std::cout << file.gcount();
    file.close();

    std::cout << "Size of argument : " << sizeof(arg) << '\n';
    //TODO: CALL
    std::cout << "result : " << func(&arg, &image[0]) << '\n';
    std::cout << "Size of image : " << sizeof(image) << '\n';

    file.open("../output.bmp", std::ios::out);
    file.write(dib, 54);
    file.write(image, sizeof(image));
    file.close();

    //file.open("../hed.mine", std::ios::out);
    //file.write(dib, 54);//store backup DIB
    //file.close();
    //std::cout << (int)(image[269999] & 0xFF);//check if whole array was filled
    return 0;
}