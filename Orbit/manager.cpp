#include "body.h"

manager::manager(vector<body *> objects)
{
    bodies = objects;
    nextFrame.clear();
    currentFrame.clear();
};

void manager::addForce(gravWell grav)
{
    nextFrame.push_back(grav);
};

void manager::update()
{
    //currentFrame = nextFrame;
    //nextFrame.clear();
    for (int i = 0; i < size(bodies); i++)
    {
        addForce(gravWell((*bodies[i]).getLocation(), (*bodies[i]).getMass()));
    }

    for (int i = 0; i < size(bodies); i++)
    {
        for (int j = 0; j < size(nextFrame); j++)
        {
            (*bodies[i]).update(nextFrame[j]);
        }
        (*bodies[i]).draw();
    }
    nextFrame.clear();
};