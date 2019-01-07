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
    struct __attribute__((aligned(16))) data_julia
    {
        __int64_t width;
        __int64_t height;
        double step_I;
        double step_R;
        double left_down_I;
        double left_down_R;
        double const_Im;
        double const_Re;
        double radius;
        __int64_t depth;
    };

    void recalc_step();
    data_julia my_data;
    double up_Im;
    double down_Im;
    double left_Re;
    double right_Re;
public:
    Raw_Julia() : Raw_Julia(900, 900) {};
    Raw_Julia(u_int width, u_int height);

    void set_square(double right_x, double left_x, double top_y, double down_y);
    void set_size(u_int size);
    void set_size(u_int width, u_int height);
    void set_algorithm_radius(double radius);
    void set_Z_constant(double Re, double Im);
    void set_depth(u_int depth);

    void use_julia(u_int8_t *array);
};


#endif //JULIA_X86_64_RAW_JULIA_H
