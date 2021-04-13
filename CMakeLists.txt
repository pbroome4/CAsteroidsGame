CMAKE_MINIMUM_REQUIRED(VERSION 3.16.3)
PROJECT(ASTEROIDS VERSION 0.1)


add_executable(Asteroids main.c player.c asteroid.c)

target_include_directories(Asteroids PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Asteroids m allegro allegro_primitives)