//
// Created by przemek on 1/6/19.
//

#include <fstream>
#include "Raw_Julia.h"

extern "C"
{
  int gen_Julia(void *argument, char *array);
}

Raw_Julia::DIB Raw_Julia::calc_DIB_and_padding(data_julia &data)
{
  DIB ret;
  ret.height = data.height;
  ret.width = data.width;
  u_int pad = (ret.width*3)%4;
  ret.RAW_SIZE = (ret.width + pad) * ret.height; //?? unnescesary
  ret.FILE_SIZE = ret.RAW_SIZE + ret.OFFSET;
  return ret;
}

Raw_Julia::Raw_Julia(u_int width, u_int height)
{
  my_data.width = width;
  my_data.height = height;
  my_data.step_R = 0.0003;
  my_data.step_I = 0.0003;
  my_data.left_up_R = -1.5;
  my_data.left_up_I = -1.5;
  my_data.radius = 3.0;
}

std::unique_ptr<char> Raw_Julia::generate()
{
  char * ret = new char[my_DIB.RAW_SIZE*3];
  if(gen_Julia(&my_data, ret))
  {
    throw std::runtime_error("unknown error -> null data");
  }
  else
  {
    return std::unique_ptr<char>(ret);
  }
}

void Raw_Julia::save_file(std::string filename)
{
  my_DIB = calc_DIB_and_padding(my_data);
  char * image = new char[my_DIB.RAW_SIZE*3];
  std::fstream file;
  file.open(filename, std::ios::out);
  file.write((char*)&my_DIB, 54);
  gen_Julia(&my_data, image);
  file.write(image, my_DIB.RAW_SIZE*3);
  file.close();
  delete[] image;
}

void Raw_Julia::set_size(u_int width, u_int height) {

}

void Raw_Julia::set_size(u_int size) {

}

void Raw_Julia::set_square(double top_left_x, double top_left_y, double bottom_right_x, double bottom_right_y) {

}
