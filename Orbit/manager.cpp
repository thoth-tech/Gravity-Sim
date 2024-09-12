#include "body.h"

gravManager::gravManager(vector<body *> objects, double _simSpeed)
{
    bodies = objects;
    nextFrame.clear();
    pause = false;
    baseSpeed = _simSpeed;
    simSpeed = _simSpeed;
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
    update(baseSpeed);
}

void gravManager::update(double _simSpeed)
{
    draw_text(std::to_string(simSpeed), COLOR_WHITE, 20, 70);
    baseSpeed = _simSpeed;
    if (pause)
    {
        if (simSpeed > 0)
        {
            simSpeed -= 0.05;
            draw_text("PAUSING", COLOR_WHITE, 20, 80);
        }
        if (simSpeed <= 0)
        {
            simSpeed = 0;
            draw_text("PAUSED", COLOR_WHITE, 20, 80);
        }
    }
    else
    {
        if (simSpeed < baseSpeed)
        {
            simSpeed += 0.05;
        }
        if (simSpeed >= baseSpeed)
        {
            simSpeed = baseSpeed;
        }
    }
    if(simSpeed != 0)
    {
        for (int i = 0; i < size(bodies); i++)
        {
            addForce(gravWell((*bodies[i]).getLocation(), (*bodies[i]).getMass()));
        }

        for (int i = 0; i < size(bodies); i++)
        {
            for (int j = 0; j < size(nextFrame); j++)
            {
                (*bodies[i]).updateVector(nextFrame[j], simSpeed);
            }
            (*bodies[i]).updatePos(simSpeed);
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