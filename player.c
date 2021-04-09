#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <asteroids.h>
#include <player.h>


typedef struct SHIP{
    int x;
    int y;

    ALLEGRO_BITMAP *sprite;
}SHIP;

static SHIP ship;
void ship_init(){
    ship.x = BUFFER_W/2 - SHIP_W/2;
    ship.y = BUFFER_H/2 - SHIP_H/2;

    ship.sprite = al_create_bitmap(SHIP_W, SHIP_H);
    al_set_target_bitmap(ship.sprite);
    al_draw_filled_rectangle(0,0, SHIP_W, SHIP_H, al_map_rgb_f(1,0,0));
}

void ship_draw(){
    al_draw_bitmap(ship.sprite, ship.x, ship.y, 0);
}