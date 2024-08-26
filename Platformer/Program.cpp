#include "FallingObject.h"

const int REFRESH_RATE = 60;

int main()
{
    open_window("test", 800, 600);

    FallingObj testobj;
    testobj.location = point_at(400,300);
    testobj.size = 100;

    while (!key_typed(ESCAPE_KEY) && !quit_requested())
    {

        clear_screen(COLOR_WHITE);
        process_events();
        testobj.update();
        refresh_screen(REFRESH_RATE);
    }
    return 0;
}