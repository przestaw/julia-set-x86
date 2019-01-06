//
// Created by przemek on 1/6/19.
//

#ifndef JULIA_X86_64_RAW_JULIA_H
#define JULIA_X86_64_RAW_JULIA_H

#include <bits/types.h>
#include <zconf.h>
#include <bits/unique_ptr.h>

class Raw_Julia {
private:
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

    struct __attribute__((aligned(16))) data_julia
    {
        __int64_t width;
        __int64_t height;
        double step_R;
        double step_I;
        double left_up_R;
        double left_up_I;
        double radius;
    };

    DIB calc_DIB_and_padding(data_julia &data);

    data_julia my_data;
    DIB my_DIB;
public:
    Raw_Julia() : Raw_Julia(900, 900) {};
    Raw_Julia(u_int width, u_int height);

    void set_square(double top_left_x, double top_left_y, double bottom_right_x, double bottom_right_y);
    void set_size(u_int size);
    void set_size(u_int width, u_int height);
    void set_algorithm_radius(double radius);

    std::unique_ptr<char> generate();
    void save_file(std::string filename);
};


#endif //JULIA_X86_64_RAW_JULIA_H
