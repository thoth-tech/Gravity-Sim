#include "body.h"

gravManager::gravManager(vector<body *> objects)
{
    bodies = objects;
    nextFrame.clear();
    pause = false;
};

void gravManager::addForce(gravWell grav)
{
    nextFrame.push_back(grav);
};

void gravManager::setPause(bool _pause)
{
    pause = _pause;
};
bool gravManager::getPause()
{
    return pause;
};

void gravManager::update()
{
    if(!pause)
    {
        for (int i = 0; i < size(bodies); i++)
        {
            addForce(gravWell((*bodies[i]).getLocation(), (*bodies[i]).getMass()));
        }

        for (int i = 0; i < size(bodies); i++)
        {
            for (int j = 0; j < size(nextFrame); j++)
            {
                (*bodies[i]).updateVector(nextFrame[j]);
            }
            (*bodies[i]).updatePos();
            (*bodies[i]).draw();
        }
        nextFrame.clear();
    }
    else
    {
        for (int i = 0; i < size(bodies); i++)
        {
            (*bodies[i]).draw();
            point_2d textLocation = (*bodies[i]).getLocation();
            textLocation.x += 10;
            textLocation.y += 10;
            draw_text((*bodies[i]).getSpeedString(), (*bodies[i]).getColor(), textLocation.x, textLocation.y);
        }
        nextFrame.clear();
    }
};