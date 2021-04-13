#ifndef asteroid_header
    #define asteroid_header

    #define ASTEROID_W 10
    #define ASTEROID_H 10


    typedef struct ASTEROID{
        int x, y;
        int dx, dy;

        bool used;
    }ASTEROID;
    #define ASTEROIDS_N 50
    extern ASTEROID asteroids[ASTEROIDS_N];

    extern void asteroids_init();
    extern void asteroids_update();
    extern void asteroids_draw();

#endif