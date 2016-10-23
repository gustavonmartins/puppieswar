#include "I_Moveable.h"

I_Moveable::I_Moveable() {
    //ctor
}

I_Moveable::CS_3D::CS_3D(double const & ax1, double const & ax2, double const & ax3):
    axis_one(ax1),
    axis_two(ax2),
    axis_three(ax3) {}

I_Moveable::~I_Moveable() {
    //dtor
}
