#include "body.h"

gravWell::gravWell(point_2d _location, float _mass)
{
    location = _location;
    mass = _mass;
}

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

void body::updateVector(gravWell object)
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

void body::updatePos()
{
    location.x = location.x + velocity.x;
    location.y = location.y + velocity.y;
}

staticObj::staticObj(float _mass, point_2d _location, vector_2d _velocity, color _colour) : body(_mass, _location, _velocity, _colour) {}

void staticObj::updateVector(gravWell object)
{
    return;
}

void staticObj::draw()
{
    fill_circle(colour, circle_at(location, radius));
}

string staticObj::getSpeedString()
{
    return "N/A";
}

dynamic::dynamic(float _mass, point_2d _location, vector_2d _velocity, color _colour, int line_length, float _bounce, double _drag) : body(_mass, _location, _velocity, _colour) 
{
    lineLen = line_length;
    bounce = _bounce;
    dragCoef = _drag;
}

void dynamic::updateVector(gravWell object)
{
    if (bounce > 0)
    {
        if (location.x > SCREEN_WIDTH && velocity.x > 0)
        {
            velocity.x = velocity.x * -bounce;
            velocity.y = velocity.y * bounce;
        }
        if (location.x < 0 && velocity.x < 0)
        {
            velocity.x = velocity.x * -bounce;
            velocity.y = velocity.y * bounce;
        }
        if (location.y > SCREEN_HEIGHT && velocity.y > 0)
        {
            velocity.x = velocity.x * bounce;
            velocity.y = velocity.y * -bounce;
        }
        if (location.y < 0 && velocity.y < 0)
        {
            velocity.x = velocity.x * bounce;
            velocity.y = velocity.y * -bounce;
        }

        if ((location.x == object.location.x && location.y == object.location.y)) {}
        else 
        {
            velocity = vector_add(velocity, gravity(object));
            velocity = vector_add(velocity, drag());
        }
    }
    return;
}

vector_2d dynamic::gravity(gravWell obj)
{
    float angle = point_point_angle(location, obj.location);
    float dist = point_point_distance(location, obj.location);
    
    // calculations based upon the inverse square law
    double gravForce = GRAV_CONST * ((mass * obj.mass)/(dist * dist));

    return vector_from_angle(angle, gravForce/mass);
}

vector_2d dynamic::drag()
{
    double speed = vector_magnitude(velocity);
    double angle = vector_angle(velocity);
    double area = 3.14 * (radius * radius); // bodies are assumed spherical no need for a particularly accurate definition of pi
    double dragForce = DENSITY*(speed * speed) * dragCoef * area;
    return vector_invert(vector_from_angle(angle, dragForce/mass));
}

void dynamic::draw()
{
    linePoints.insert(linePoints.begin(), location);
    if (linePoints.size() > lineLen)
    {
        linePoints.resize(lineLen);
    }
    for (int i = 0; i < linePoints.size(); i++)
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