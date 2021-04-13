#include <stdio.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <asteroids.h>
#include <asteroid.h>

ASTEROID asteroids[ASTEROIDS_N];
static ALLEGRO_BITMAP *sprite;

void asteroids_init(){
    for(int i = 0; i < ASTEROIDS_N; i++){
        asteroids[i].used = false;
    }
    sprite = al_create_bitmap(ASTEROID_W, ASTEROID_H);
    al_set_target_bitmap(sprite);
    al_draw_filled_rectangle(0,0, ASTEROID_W, ASTEROID_H, al_map_rgb_f(1,0,0));
}
/**
 * spawns an asteroid outside of view and sends it toward the view
*/
#define PI 3.1416f
void spawn_asteroid(ASTEROID *asteroid){
    asteroid->used = true;
    asteroid->x = BUFFER_W/2 - ASTEROID_W/2;
    asteroid->y = BUFFER_H/2 - ASTEROID_H/2;
    int radius = (max(BUFFER_W, BUFFER_H) + max(ASTEROID_W, ASTEROID_H));
    float theta = between_f(0, 2.0*PI);
    asteroid->x += (int) (radius*cos(theta));
    asteroid->y += (int) (radius*sin(theta));

    asteroid->dx = -sgn((float) cos(theta)) * between(1,3);
    asteroid->dy = -sgn((float) sin(theta)) * between (1,3);
}

void asteroids_update(){
    //every second frame add an asteroid
    int quota = 0;
    if(!(frames % 2)){
        quota++;
    }
    for(int i = 0; i < ASTEROIDS_N; i++){
        if(!asteroids[i].used)
            if(quota){
                quota--;
                spawn_asteroid(&asteroids[i]);
            }

            if((asteroids[i].x < -ASTEROID_W && asteroids[i].dx < 0) ||
            (asteroids[i].x > BUFFER_W && asteroids[i].dx > 0) ||
            (asteroids[i].y < -ASTEROID_H && asteroids[i].dy < 0) ||
            (asteroids[i].y > BUFFER_H && asteroids[i].dy > 0)){
                asteroids[i].used = false;
                continue;
            }

            asteroids[i].x += asteroids[i].dx;
            asteroids[i].y += asteroids[i].dy;
    }

}
void asteroids_draw(){
    for(int i = 0; i < ASTEROIDS_N; i++){
        if(!asteroids[i].used){
            continue;
        }
        al_draw_bitmap(sprite, asteroids[i].x, asteroids[i].y, 0);
    }
}
   