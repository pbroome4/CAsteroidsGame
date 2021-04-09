#ifndef asteroids
    #define asteroids
    #include <allegro5/allegro.h>

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