#include <stdio.h>
#include <allegro5/allegro.h>

// Timers are event sources that will send regular timed events 
// at a given interval.  They can be used to regulate your main 
// update loop, so you only run at a given FPS, or they can be
// used to know when an animation needs to update, etc.

// This program builds on the 'events.cc' program to have a regular
// update frequency

const float FPS = 60;
// Rate we want to limit our update logic to

int main (int argc, char **argv) {

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    bool redraw = true;

    if (!al_init()) {
        fprintf(stderr, "Couldn't initialize Allegro!\n");
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    // Initialize the timer to tick 1.0/FPS seconds per tick
    if (!timer) {
        fprintf(stderr, "Couldn't create timer!\n");
        return -1;
    }

    display = al_create_display(640, 480);
    if (!display) {
        fprintf(stderr, "Couldn't create display!\n");
        al_destroy_timer(timer);
        return -1;
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "Couldn't create event queue!\n");
        al_destroy_timer(timer);
        al_destroy_display(display);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));


    // Register the timer's event source in our event queue so we
    // can fetch the events later.
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_clear_to_color(al_map_rgb(0,0,0));

    al_flip_display();

    al_start_timer(timer); // Start timer

    while(1) {

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        // Since we have regular events coming in, we don't need to
        // worry about getting stuck in the 'wait' function. This
        // function will wait forever if no event comes in.

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        }
        // Check for the timer event.  If the event is a timer event,
        // trigger a redraw.

        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            al_flip_display();
        }
        // The && is necessary because without it, the update loop
        // would fall behind.  So we want to make sure both the redraw
        // is true and the event queue is empty before we do the actual
        // redraw.
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
