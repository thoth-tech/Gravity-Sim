#include <vector>
#include <cmath>
#include <string>
#include "splashkit.h"
#define REFRESH_RATE 60
#define GRAV_CONST 1 // may need to be modified depending on initial condition
#define DENSITY 0.0005
#define SCREEN_HEIGHT 900
#define SCREEN_WIDTH 1600

class gravWell
{
public:
    point_2d location;
    float mass;
    gravWell(point_2d _location, float _mass);
};

class body
{
protected:
    point_2d location;
    float mass;
    color colour;
    float radius;

public:
    vector_2d velocity;
    body(float _mass, point_2d _location, vector_2d _velocity, color _colour);

    point_2d getLocation();
    float getMass();
    color getColor();

    virtual void updateVector(gravWell object);
    virtual void updatePos();
    virtual void draw();
    virtual string getSpeedString();
};

class gravManager
{
protected:
    vector<body *> bodies;
    vector<gravWell> nextFrame;
    bool pause;

public:
    gravManager(vector<body *> objects);
    bool getPause();
    void setPause(bool _pause);
    void addForce(gravWell grav);
    void update();
    void create();
};

class dynamic : public body 
{
    protected:
        vector<point_2d> linePoints;
        int lineLen;
        vector_2d gravity(gravWell object);
        vector_2d drag();
        float bounce;
        double dragCoef;

    public:
        dynamic(float _mass, point_2d _location, vector_2d _velocity, color _colour, int line_length, float _bounce, double _drag);
        void updateVector(gravWell object);
        void updatePos();
        void draw();
        string getSpeedString();
};

class staticObj : public body
{
    protected:

    public:
        staticObj(float _mass, point_2d _location, vector_2d _velocity, color _colour);
        void updateVector(gravWell object);
        void draw();
        string getSpeedString();
};

class bodyFactory
{
public:
    virtual body *createBody(point_2d pos, vector_2d velocity, float mass, color clr) = 0;
};

class staticFac : public bodyFactory
{
public:
    body *createBody(point_2d pos, vector_2d velocity, float mass, color clr);
};

class dynamicFac : public bodyFactory
{
protected:
    float bounce;
    double drag;
    int line_length;

public:
    dynamicFac(float _bounce, double _drag, int _line_length);
    body *createBody(point_2d pos, vector_2d velocity, float mass, color clr);
};