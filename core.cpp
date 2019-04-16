#include <SDL2/SDL.h>
#include <emscripten.h>
#include <emscripten/bind.h>
#include <cstdlib>
#include "Entity.h"

Entity entity;
SDL_Window *window;

void mainloop(void *arg)
{
    SDL_Renderer *renderer = static_cast<SDL_Renderer *>(arg);

    // example: draw a moving rectangle

    // red background
    SDL_SetRenderDrawColor(renderer, 88, 88, 88, 255);
    SDL_RenderClear(renderer);

    // moving blue rectangle
    entity.update();
    entity.draw(renderer);
}

void setWindowSize(int w, int h)
{
    SDL_SetWindowSize(window, w, h);
}

EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::function("setWindowSize", &setWindowSize);
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Renderer *renderer;
    int sizeW, sizeH;
    SDL_CreateWindowAndRenderer(50, 50, SDL_WINDOW_RESIZABLE, &window, &renderer);
    SDL_SetWindowSize(window, 640, 480);

    const int simulate_infinite_loop = 1; // call the function repeatedly
    const int fps = -1;                   // call the function as fast as the browser wants to render (typically 60fps)
    emscripten_set_main_loop_arg(mainloop, renderer, fps, simulate_infinite_loop);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
