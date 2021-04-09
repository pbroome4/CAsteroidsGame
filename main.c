#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <asteroids.h>
#include <player.h>

// general stuff
void must_init(bool test, char *desc){
    if(test == false){
        printf("%s failed to init\n", desc);
        exit(1);
    }
}

// display
//------------------------------------------------
#define DISP_W 512
#define DISP_H 512
ALLEGRO_DISPLAY *disp;
ALLEGRO_BITMAP *back_buffer;

void disp_init(){
    disp = al_create_display(DISP_W, DISP_H);
    must_init(disp, "display");
    back_buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    must_init(back_buffer, "back buffer");
}

void disp_deinit(){
    al_destroy_display(disp);
    al_destroy_bitmap(back_buffer);
}

void disp_pre_draw(){
    al_set_target_bitmap(back_buffer);
    al_clear_to_color(al_map_rgb_f(0, 0, 0));
}

void disp_post_draw(){
    al_set_target_bitmap(al_get_backbuffer(disp));
    al_draw_scaled_bitmap(back_buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0); 
    al_flip_display();
}

//keyboard
//-------------------------------------------------------------
#define KEY_NOT_RECORDED 1 //bit position: 0 if seen 1 if not seen
#define KEY_PRESSED 2 //bit position: 0 if not pressed, 1 if pressed
unsigned char keys[ALLEGRO_KEY_MAX];
void keyboard_init(){
    must_init(al_install_keyboard(), "keyboard");
    memset(keys, 0, sizeof(keys));
}
void keyboard_update(ALLEGRO_EVENT event){
    switch(event.type){
        case ALLEGRO_EVENT_TIMER:
            for(int i = 0; i < ALLEGRO_KEY_MAX; i++){
                //sets KEY_NOT_RECORDED bit to 0
                keys[i] &= ~KEY_NOT_RECORDED;
            }
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            //set KEY_PRESSED and KEY_NOT_RECORDED bits to high
            keys[event.keyboard.keycode] |= KEY_PRESSED + KEY_NOT_RECORDED;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            //set KEY_PRESSED bit low;
            keys[event.keyboard.keycode] &= ~KEY_PRESSED;
            break;
    }
}


//main logic
#define FPS 30.0

int main(int argc, char **argv){
    must_init(al_init(), "allegro");
    must_init(al_init_primitives_addon(), "allegro_primitives");


    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    must_init(queue, "event queue");

    ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);
    must_init(timer, "timer");

    disp_init();
    keyboard_init();
    ship_init();

    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    ALLEGRO_EVENT event;
    bool done = false;
    al_start_timer(timer);
    while(1){
        al_wait_for_event(queue, &event);
        keyboard_update(event);

        switch(event.type){
            case ALLEGRO_EVENT_TIMER:                
                if(keys[ALLEGRO_KEY_ESCAPE]){
                    done = true;
                    break;
                }

                disp_pre_draw();
                ship_draw();
                disp_post_draw();

                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }
        if(done == true){
            break;
        }
    }


    disp_deinit();
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
}
