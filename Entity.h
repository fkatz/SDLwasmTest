#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>
#include <string>

class Entity
{
  private:
    SDL_Rect rect;
    SDL_Event event;

  public:
    Entity()
    {
        rect.x = 0;
        rect.y = 50;
        rect.w = 50;
        rect.h = 50;
    };

    Entity(int x, int y, int w, int h)
    {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
    };
    void update()
    {
        SDL_PumpEvents();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_WINDOWEVENT_RESIZED)
            {
                std::string log;
                std::stringstream ss;
                ss << event.window.data1;
                log = "console.log('Resize: " + ss.str() + "')";
                emscripten_run_script(log.c_str());
            }
            if(event.type== SDL_MOUSEBUTTONDOWN){
                emscripten_run_script("console.log('Mousedown')");
            }
        }
        SDL_GetMouseState(&rect.x, &rect.y);
    };
    void draw(SDL_Renderer *renderer)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
    };
    void setPosition(int x, int y, int w, int h);
    SDL_Rect getRect(){
        return rect;
    };
};