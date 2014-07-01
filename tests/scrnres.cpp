#include "stdio.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"

int main (int argc, char **argv) {

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_DISPLAY_MODE disp_data;

    // ALLEGRO_DISPLAY_MODE contains information about a supported
    // fullscreen display mode
    // The struct is
    /* 
       typedef struct ALLEGRO_DISPLAY_MODE {
            int width;        // Screen width
            int height;       // Screen height
            int format;       // The pixel format of the mode
            int refresh_rate; // The refresh rate of the mode
    */

    if (!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro.\n");
        return -1;
    }

    al_init_image_addon();
    al_init_primitives_addon();

    al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

    // First arg is the index of the display mode we want, and the 
    // "al_get_display_mode" function fills the disp_data struct with
    // info.  "al_get_num_display_modes" gives us the number of 
    // resolutions the screen can handle, and subtracting 1 will give
    // us the maximum resolution for your screen.  Passing "0" as the
    // first argument will give you the minimum resolution.

    al_set_new_display_flags(ALLEGRO_FULLSCREEN);

    // Tells Allegro to display in fullscreen

    display = al_create_display(disp_data.width, disp_data.height);

    // PROTIP: Instead of using hard-coded coordinates for an image,
    // use percentages so the display can adapt to any resolution

    al_rest(3);
    al_destroy_display(display);

    return 0;
}
