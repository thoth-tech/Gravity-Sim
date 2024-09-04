#include "body.h"

body *staticFac::createBody(point_2d pos, vector_2d velocity, float mass, color clr) 
{
    return new staticObj(mass, pos, velocity, clr);
}

dynamicFac::dynamicFac(float _bounce, double _drag, int _line_length)
{
    bounce = _bounce;
    drag = _drag;
    line_length = _line_length;
}

body *dynamicFac::createBody(point_2d pos, vector_2d velocity, float mass, color clr)
{
    return new dynamic(mass, pos, velocity, clr, line_length, bounce, drag);
}