#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <asteroids.h>
#include <player.h>
#include <asteroid.h>

// general stuff
void must_init(bool test, char *desc){
    if(test == false){
        printf("%s failed to init\n", desc);
        exit(1);
    }
}

/**
 * rand int between [x,y)
 */
int between(int x, int y){
    return rand()%(y-x) + x;
}

float between_f(float x, float y){
    return (y-x) * ((float)rand() / RAND_MAX) + x;
}

bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2){
    if(ax2 < bx1 || ay2 < by1 || ax1 > bx2 || ay1 > by1)
        return false;
    
    return true;
}

int max(int a, int b){
    return (a > b)? a : b;
}
int sgn(float x){
    if(x > 0){
        return 1;
    }
    if (x == 0.0){
        return 0;
    }
    return -1;
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
long frames;
bool game_over;

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
    asteroids_init();

    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    frames = 0;
    srand((unsigned int) time(NULL));

    ALLEGRO_EVENT event;
    game_over = false;
    bool redraw = true;
    al_start_timer(timer);
    while(1){
        al_wait_for_event(queue, &event);
        keyboard_update(event);

        switch(event.type){
            case ALLEGRO_EVENT_TIMER:                
                if(keys[ALLEGRO_KEY_ESCAPE]){
                    game_over = true;
                    break;
                }

                ship_update();
                asteroids_update();

                frames++;
                redraw = true;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                game_over = true;
                break;
        }
        if(game_over == true){
            break;
        }

        if(redraw){
            disp_pre_draw();
            ship_draw();
            asteroids_draw();
            disp_post_draw();
        }
    }


    disp_deinit();
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
}
