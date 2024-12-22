#include<bits/stdc++.h>
#include "inc/SDL.h"
// This is a c++ code for bouncing ball simulation using SDL.
// To run this code on your own device
// Step 1: Clone the git repository
// Step 2: run the following command on your terminal
//      1: g++ -o main Bouncy_Ball.cpp -IC\include -LC:lib -lSDL2main -lSDL2
//      2: ./main

#undef main
using namespace std;
#define WIDTH 500
#define HEIGHT 500
#define WHITE 0xffffffff
#define g 0.2

struct Circle {
    double x;
    double y;
    double r;
    double v_x;
    double v_y;
};

void fillCircle(SDL_Surface* surface, struct Circle circle) {
    double l_x = circle.x - circle.r;
    double l_y = circle.y - circle.r;
    double h_x = circle.x + circle.r;
    double h_y = circle.y + circle.r;

    double radius_square = circle.r * circle.r;

    for (double x = l_x; x <= h_x; x++) {
        for (double y = l_y; y <= h_y; y++) {
            double d = (x - circle.x) * (x - circle.x) + (y - circle.y) * (y - circle.y);
            if (d < radius_square) {
                SDL_Rect pixel = {static_cast<int>(x), static_cast<int>(y), 1, 1};
                SDL_FillRect(surface, &pixel, WHITE);
            }
        }
    }
}

void step(struct Circle* circle) {
    circle->x += circle->v_x;
    circle->y += circle->v_y;

    circle->v_y += g;

    if(circle->x + circle->r > WIDTH){
        circle->x = WIDTH-circle->r;
        circle->v_x *= -0.9;
    }
    if(circle->x - circle->r < 0){
        circle->x = circle->r;
        circle->v_x *= -0.9;
    }

    if(circle->y + circle->r > HEIGHT){
        circle->y = HEIGHT-circle->r;
        circle->v_y *= -0.9;
    }
    if(circle->y - circle->r < 0){
        circle->y = circle->r;
        circle->v_y *= -0.9;
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    struct Circle circle = {90, 90, 90, 4, 5};

    SDL_Rect erase_rec = {0, 0, WIDTH, HEIGHT};
    SDL_Event event;
    bool run = true;
    while (run) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                run = false;
            }
        }

        SDL_FillRect(surface, &erase_rec, 0x000000);

        fillCircle(surface, circle);
        step(&circle);

        SDL_UpdateWindowSurface(window);
        SDL_Delay(20);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
