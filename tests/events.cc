#include <stdio.h>
#include <allegro5/allegro.h>

// Events tell you that something in your program has happened
// (key press, mouse click, timer tick, etc.).  Allegro uses 
// them to notify you of an action, but custom events may be
// created

// An event source is something that notifies the program when
// something has occurred, such as the Allegro Timers, Displays
// and Inputs

// An event queue is where events are placed in a 
// first-in-first-out container and are removed when the events
// are being handled by the main program.  You may create
// multiple event queues and direct the events into the 
// appropriate queue.

int main (int argc, char **argv) {

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;

    if (!al_init()) {
        fprintf(stderr, "Could not initialize Allegro!\n");
        return -1;
    }

    display = al_create_display(640, 480);
    if (!display) {
        fprintf(stderr, "Could not create display!\n");
        return -1;
    }

    event_queue = al_create_event_queue();  // Returns NULL on failure
    if (!event_queue) {
        fprintf(stderr, "Could not create event queue!\n");
        al_destroy_display(display);
        return -1;
    }
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    // With this function, we tie the display to the event queue so we can
    // be informed of events such as the 'close event'.  Without this,
    // the display events will not be placed in this queue and will not be
    // handled.


    al_clear_to_color(al_map_rgb(0,0,0));

    al_flip_display();

    while(1) {

        ALLEGRO_EVENT ev;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.06);
        // This function initializes an ALLEGRO_TIMEOUT object to some number,
        // in this case, 0.06 seconds or 60ms.


        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
        // This tells Allegro to wait until an event arrives, or until the
        // timeout expires, whichever is first.  'al_wait_for_event_until'
        // will return false if it didn't return an event before the timeout

        if (get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        // This checks for an event in the event queue.  If the event is a
        // 'Display close event', break the loop

        al_clear_to_color(al_map_rgb(0,0,0));
        al_flip_display();

    }

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;

}
