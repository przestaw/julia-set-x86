//
// Created by przemek on 1/6/19.
//

#include <fstream>
#include <cmath>
#include "../include/Raw_Julia.h"

extern "C"
{
  int gen_Julia(void *argument, u_int8_t *array);
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
  my_data.step_I = 0.002;
  my_data.step_R = 0.002;
  my_data.left_down_I = -1.0;
  my_data.left_down_R = -1.0;
  my_data.const_Im = 0.76;
  my_data.const_Re = 0.005;
  my_data.radius = 6.0;
  my_data.depth = 23;
}

void Raw_Julia::save_file(std::string filename)
{
  my_DIB = calc_DIB_and_padding(my_data);
  u_int8_t* image = new u_int8_t[my_DIB.RAW_SIZE*3];
  std::fstream file;
  file.open(filename, std::ios::out);
  file.write((char*)&my_DIB, 54);
  gen_Julia(&my_data, image);
  file.write((char*)image, my_DIB.RAW_SIZE*3);
  file.close();
  delete[] image;
}

void Raw_Julia::set_size(u_int width, u_int height)
{
  my_data.height = height;
  my_data.width = width;
  recalc_step();
}

void Raw_Julia::set_size(u_int size)
{
  my_data.width = size;
  my_data.height = size;
  recalc_step();
}

void Raw_Julia::set_square(double right_x, double left_x, double top_y, double down_y)
{
  this->up_Im = top_y;
  this->down_Im = down_y;
  this->left_Re = left_x;
  this->right_Re = right_x;
  my_data.left_down_I = down_Im;
  my_data.left_down_R = left_Re;
  this->recalc_step();
}

void Raw_Julia::set_Z_constant(double Re, double Im)
{
  my_data.const_Re = Re;
  my_data.const_Im = Im;
}

void Raw_Julia::set_algorithm_radius(double radius)
{
  my_data.radius = radius;
}

void Raw_Julia::set_depth(u_int depth)
{
  my_data.depth = depth;
}

void Raw_Julia::recalc_step()
{
  my_data.step_I = fabs(up_Im-down_Im)/my_data.height;
  my_data.step_R = fabs(left_Re-right_Re)/my_data.width;
}

void Raw_Julia::use_julia(u_int8_t *array)
{
  recalc_step();
  gen_Julia(&my_data, array);
}
