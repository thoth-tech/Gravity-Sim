#include "body.h"

int main()
{
    open_window("newtonian gravity sim", SCREEN_WIDTH, SCREEN_HEIGHT);

    bodyFactory* fac1 = new staticFac;
    bodyFactory* fac2 = new dynamicFac(0.5, 0.005, 1000);

    body *statObj = fac1->createBody(point_at(800, 450), vector_from_angle(0, 0), 600, COLOR_BRIGHT_GREEN);
    body *dynObj1 = fac2->createBody(point_at(800, 550), vector_from_angle(0, 1.5), 2, COLOR_WHITE);
    body *dynObj2 = fac2->createBody(point_at(800, 650), vector_from_angle(0, 1.7), 2, COLOR_VIOLET);
    body *dynObj3 = fac2->createBody(point_at(800, 350), vector_from_angle(0, 1), 2, COLOR_BLUE);
    body *dynObj4 = fac2->createBody(point_at(800, 300), vector_from_angle(0, 1), 20, COLOR_RED);

    vector<body*> objects = {statObj, dynObj1, dynObj2, dynObj3, dynObj4};

    gravManager gravSystem = gravManager(objects);

    int clickMass = 0;

    double simSpeed = 1;

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
        if (key_typed(SPACE_KEY))
        {
            gravSystem.setPause(!gravSystem.getPause());
        }
        if (key_typed(UP_KEY))
        {
            simSpeed += 0.1;
        }
        if (key_typed(DOWN_KEY))
        {
            simSpeed -= 0.1;
        }

        gravSystem.update(simSpeed);
        refresh_screen(REFRESH_RATE);
    }
    return 0;
}