#include <vector>
#include <cmath>
#include <string>
#include "splashkit.h"
#define REFRESH_RATE 60
#define GRAV_CONST 1 // may need to be modified depending on initial condition
#define SCREEN_HEIGHT 900
#define SCREEN_WIDTH 1600

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
        color getColor();

        virtual void update(vector<body*> objects);
        virtual void draw();
        virtual string getSpeedString();

    
};

class dynamic : public body 
{
    protected:
        vector<point_2d> linePoints;
        int lineLen;
        vector_2d gravity(body obj);
        bool bounce;

    public:
        dynamic(float _mass, point_2d _location, vector_2d _velocity, color _colour, int line_length, bool _bounce);
        void update(vector<body *> objects);
        void draw();
        string getSpeedString();
};

class staticObj : public body
{
    protected:

    public:
        staticObj(float _mass, point_2d _location, vector_2d _velocity, color _colour);
        void update(vector<body *> objects);
        void draw();
        string getSpeedString();
};