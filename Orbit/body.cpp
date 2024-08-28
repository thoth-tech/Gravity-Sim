#include "body.h"

body::body(float _mass, point_2d _location, vector_2d _velocity, color _colour)
{
    mass = _mass;
    location = _location;
    velocity = _velocity;
    colour = _colour;
    radius = sqrt(mass/3.14);
}

point_2d body::getLocation()
{
    return location;
}

float body::getMass()
{
    return mass;
}

void body::update(vector<body *> objects)
{
    return;
}

void body::draw()
{
    return;
}

string body::getSpeedString() 
{
    return "this should not show up";
}

color body::getColor()
{
    return colour;
}

staticObj::staticObj(float _mass, point_2d _location, vector_2d _velocity, color _colour) : body(_mass, _location, _velocity, _colour) {}

void staticObj::update(vector<body *> objects)
{
    return;
}

void staticObj::draw()
{
    location.x = location.x + velocity.x;
    location.y = location.y + velocity.y;
    fill_circle(colour, circle_at(location, radius));
}

string staticObj::getSpeedString()
{
    return "N/A";
}

dynamic::dynamic(float _mass, point_2d _location, vector_2d _velocity, color _colour, int line_length, bool _bounce) : body(_mass, _location, _velocity, _colour) 
{
    lineLen = line_length;
    bounce = _bounce;
}

void dynamic::update(vector<body*> objects)
{
    for (int i = 0; i < size(objects); i++)
    {
        if (bounce)
        {
            if (location.x > SCREEN_WIDTH || location.x < 0)
            {
                velocity.x = velocity.x * -1;
            }
            if (location.y > SCREEN_HEIGHT || location.y < 0)
            {
                velocity.y = velocity.y * -1;
            }
        }

        if ((location.x == (*objects[i]).getLocation().x && location.y == (*objects[i]).getLocation().y)) {}
        else 
        {
            velocity = vector_add(velocity, gravity((*objects[i])));
        }
    }
    linePoints.insert(linePoints.begin(), location);
    if (linePoints.size() > lineLen)
    {
        linePoints.resize(lineLen);
    }
    return;
}

vector_2d dynamic::gravity(body obj)
{
    float angle = point_point_angle(location, obj.getLocation());

    //float cogX = ((location.x * mass) + (obj.getLocation().x * obj.getMass())) / (mass + obj.getMass());
    //float cogY = ((location.y * mass) + (obj.getLocation().y * obj.getMass())) / (mass + obj.getMass());

    //float dist = point_point_distance(location, point_at(cogX, cogY));

    //calculations based upon the inverse square law
    float dist = point_point_distance(location, obj.getLocation());
    float gravForce = GRAV_CONST * ((mass*obj.getMass())/(dist * dist));

    return vector_from_angle(angle, gravForce/mass);
}

void dynamic::draw()
{
    location.x = location.x + velocity.x;
    location.y = location.y + velocity.y;\
    for (int i; i < linePoints.size(); i++)
    {
        if (i > 0)
        {
            draw_line(colour, line_from(linePoints[i-1], linePoints[i]));
        }
    }
    fill_circle(colour, circle_at(location, radius));
}

string dynamic::getSpeedString()
{
    return std::to_string(vector_magnitude(velocity));
}