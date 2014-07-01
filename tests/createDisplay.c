#include <stdio.h>
#include <allegro5/allegro.h>

int main (int argc, char **argv) {

    ALLEGRO_DISPLAY *display = NULL;  // Create display array

    if (!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro.\n");
        return -1;
    }

    // al_init() initializes the Allegro system.  This must be called
    // before any other Allegro functions are called.  This function is
    // equivalent to "al_install_system(ALLEGRO_VERSION_INT, atexit)"
    // and returns a boolean; true on successful init and false if
    // Allegro can't be used

    display = al_create_display(640, 480);
    if (!display) {
        fprintf(stderr, "Failed to create display.\n");
        return -1;
    }

    al_clear_to_color(al_map_rgb(0,0,0));

    // Clears the target bitmap to the given color (in this case black)
    // and doesn't return

    al_flip_display();

    // Switches the two image buffers around s.t the first image buffer
    // is displayed to the user and the other is the buffer you will draw
    // on.  Allegro by default creates two image buffers, one for the user
    // to see, and the other that is drawn in the code.  Failing to call
    // this function will give us only a single blank image buffer on
    // the screen

    al_rest(10.0);

    // al_rest makes the program rest for the specified time (in seconds).
    // It takes floating point numbers greater than 0.

    al_destroy_display(display);

    // free the memory

    return 0;
}

