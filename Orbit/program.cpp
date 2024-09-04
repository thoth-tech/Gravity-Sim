#include "body.h"

//TODO: factory interface, object manager class, observer, friction and relativity.

int main()
{
    open_window("newtonian gravity sim", SCREEN_WIDTH, SCREEN_HEIGHT);

    ////staticObj statObj = staticObj(300, point_at(800, 450), vector_from_angle(0, 0), COLOR_BRIGHT_GREEN);
    //dynamic statObj = dynamic(600, point_at(800, 450), vector_from_angle(0, 0), COLOR_BRIGHT_GREEN, 100, 1, 0.05);
    //dynamic dynObj1 = dynamic(2, point_at(800, 550), vector_from_angle(0, 1.5), COLOR_AZURE, 1000, 1, 0.05);
    //dynamic dynObj2 = dynamic(20, point_at(800, 300), vector_from_angle(0, 1), COLOR_RED, 1000, 1, 0.05);
    //0.0005*DENSITY;
    //vector<body*> objects = {&statObj, &dynObj1, &dynObj2};
    bodyFactory* fac1 = new staticFac;
    bodyFactory* fac2 = new dynamicFac(0.5, 0.005, 1000);

    body *statObj = fac1->createBody(point_at(800, 450), vector_from_angle(0, 0), 600, COLOR_BRIGHT_GREEN);
    body *dynObj1 = fac2->createBody(point_at(800, 550), vector_from_angle(0, 1.5), 2, COLOR_WHITE);
    body *dynObj2 = fac2->createBody(point_at(800, 650), vector_from_angle(0, 1.7), 2, COLOR_VIOLET);
    body *dynObj3 = fac2->createBody(point_at(800, 350), vector_from_angle(0, 1), 2, COLOR_BLUE);
    body *dynObj4 = fac2->createBody(point_at(800, 300), vector_from_angle(0, 1), 20, COLOR_RED);

    vector<body*> objects = {statObj, dynObj1, dynObj2, dynObj3, dynObj4};

    manager gravSystem = manager(objects);

    int clickMass = 0;

    while (!key_typed(ESCAPE_KEY) && !quit_requested())
    {
        clear_screen(COLOR_BLACK);
        process_events();

        clickMass += mouse_wheel_scroll().y;

        draw_text(std::to_string(clickMass), COLOR_WHITE, 20, 50);

        //update changes the velocity vectors based upon the locations and mass of the bodies
        if (mouse_down(LEFT_BUTTON))
        {
            gravSystem.addForce(gravWell(mouse_position(), clickMass));
        }
        gravSystem.update();

        //draw both changes the current position* of each body as well as drawing it
        //*current position is changed in draw rather than update to prevent execution order from effecting the physics calculations
        //for (int i = 0; i < size(objects); i++)
        //{
        //    draw_text((*objects[i]).getSpeedString(), (*objects[i]).getColor(), 20, 50 + (i * 20));
        //    (*objects[i]).draw();
        //}
        
        refresh_screen(REFRESH_RATE);
    }
    return 0;
}