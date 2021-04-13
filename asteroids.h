#ifndef asteroids_header
    #define asteroids_header
    #include <allegro5/allegro.h>

    //frames that have passed
    extern long frames;
    extern bool game_over;
/**
 * basic collision checking. checks if the two rectangles are over lapping
 * (x1, y1) will be top left coord of object. (x2, y2) is bottom right coord of object
 */
    extern bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);
    extern int between(int x, int y);
    extern float between_f(float x, float y);
    extern int max(int a, int b);
    extern int sgn(float x);

    #define BUFFER_W 256
    #define BUFFER_H 256
    extern ALLEGRO_BITMAP *backBuffer;
    extern void disp_init();
    extern void disp_deinit();
    extern void disp_pre_draw();
    extern void disp_post_draw();

    extern unsigned char keys[ALLEGRO_KEY_MAX];
    extern void keyboard_init();
    extern void keyboard_update();

    

#endif