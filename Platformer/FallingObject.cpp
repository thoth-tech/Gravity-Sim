#include "FallingObject.h"

circle FallingObj::make_circle()
{
    return circle_at(location, size);
}

void FallingObj::update()
{
    // basic example of simple newtonian gravity where an object accelerates downwards with a constant acceleration
    velocity.y = velocity.y + 1;

    if (location.y >= 600)
    {
        // randomises vertical impulse at the bottom of the screen so that the object bounces a random height
        velocity.y = -1*rnd(10,40);
    }


    location.x = location.x + velocity.x;
    location.y = location.y + velocity.y;
}

void FallingObj::draw()
{
    fill_circle(colour, make_circle());
}