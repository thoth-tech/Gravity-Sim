#include "FallingObject.h"

circle FallingObj::make_circle()
{
    return circle_at(location, size);
}

void FallingObj::update()
{
    velocity.y = velocity.y + 1;

    if (location.y >= 600)
    {
        velocity.y = -1*rnd(10,40);
    }


    location.x = location.x + velocity.x;
    location.y = location.y + velocity.y;

    fill_circle(COLOR_BRIGHT_GREEN, make_circle());
}