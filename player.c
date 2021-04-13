#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <asteroids.h>
#include <player.h>
#include <asteroid.h>

typedef struct SHIP{
    int x;
    int y;
    int lives;
    int blink;

    ALLEGRO_BITMAP *sprite;
}SHIP;

static SHIP ship;
void ship_init(){
    ship.x = BUFFER_W/2 - SHIP_W/2;
    ship.y = BUFFER_H/2 - SHIP_H/2;
    ship.lives = 10;
    ship.blink = 0;

    ship.sprite = al_create_bitmap(SHIP_W, SHIP_H);
    al_set_target_bitmap(ship.sprite);
    al_draw_filled_rectangle(0,0, SHIP_W, SHIP_H, al_map_rgb_f(0,0,1));
}

void ship_draw(){
    al_draw_bitmap(ship.sprite, ship.x, ship.y, 0);
}

void ship_update(){
    if(keys[ALLEGRO_KEY_UP]){
        ship.y -= SHIP_SPEED;
    }    
    if(keys[ALLEGRO_KEY_DOWN]){
        ship.y += SHIP_SPEED;
    }
    if(keys[ALLEGRO_KEY_LEFT]){
        ship.x -= SHIP_SPEED;
    }
    if(keys[ALLEGRO_KEY_RIGHT]){
        ship.x += SHIP_SPEED;
    }

    for(int i = 0; i < ASTEROIDS_N; i++){
        if(!asteroids[i].used){
            continue;
        }
        if(collide(ship.x, ship.y, ship.x+SHIP_W, ship.y+SHIP_H,
        asteroids[i].x, asteroids[i].y, asteroids[i].x + ASTEROID_W, asteroids[i].y + ASTEROID_H)){
            asteroids[i].used = false;
            ship.lives--;
        }

        if(ship.lives <= 0){
            game_over = true;
        }
    }

}