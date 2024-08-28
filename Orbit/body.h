#include <vector>
#include <cmath>
#include "splashkit.h"
#define REFRESH_RATE 60
#define GRAV_CONST 20 // may need to be modified depending on initial condition

class body
{
    protected:
        point_2d location;
        float mass;
        vector_2d velocity;
        color colour;
        float radius;

    public:
        body(float _mass, point_2d _location, vector_2d _velocity, color _colour);

        point_2d getLocation();
        float getMass();

        virtual void update(vector<body*> objects);
        virtual void draw();

    
};

class dynamic : public body 
{
    protected:
        vector<point_2d> linePoints;
        int lineLen;
        vector_2d gravity(body obj);

    public:
        dynamic(float _mass, point_2d _location, vector_2d _velocity, color _colour, int line_length);
        void update(vector<body *> objects);
        void draw();
};

class staticObj : public body
{
    protected:

    public:
        staticObj(float _mass, point_2d _location, vector_2d _velocity, color _colour);
        void update(vector<body *> objects);
        void draw();
};