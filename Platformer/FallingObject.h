#include "splashkit.h"

class FallingObj
{
    public:
        point_2d location;
        int size;
        vector_2d velocity;

        circle make_circle();
        void update();
};