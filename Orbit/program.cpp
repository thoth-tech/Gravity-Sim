#include "body.h"

int main()
{
    open_window("newtonian gravity sim", 16*100, 9*100);

    //staticObj statObj = staticObj(300, point_at(800, 450), vector_from_angle(0, 0), COLOR_BRIGHT_GREEN);
    dynamic statObj = dynamic(300, point_at(800, 450), vector_from_angle(0, 0), COLOR_BRIGHT_GREEN);
    dynamic dynObj1 = dynamic(20, point_at(800, 550), vector_from_angle(0, 1.5), COLOR_AZURE);
    dynamic dynObj2 = dynamic(20, point_at(800, 300), vector_from_angle(0, 1), COLOR_RED);

    vector<body*> objects = {&statObj, &dynObj1, &dynObj2};

    while (!key_typed(ESCAPE_KEY) && !quit_requested())
    {
        clear_screen(COLOR_BLACK);
        process_events();

        //update changes the velocity vectors based upon the locations and mass of the bodies
        for (int i = 0; i < size(objects); i++)
        {
            (*objects[i]).update(objects);
        }

        //draw both changes the current position* of each body as well as drawing it
        //*current position is changed in draw rather than update to prevent execution order from effecting the physics calculations
        for (int i = 0; i < size(objects); i++)
        {
            (*objects[i]).draw();
        }
        refresh_screen(REFRESH_RATE);
    }
    return 0;
}