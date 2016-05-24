#include <algorithm>
#include <iostream>
#include <SDL2/SDL.h>
#include "neural.h"

#define SCREEN_HEIGHT 500
#define SCREEN_WIDTH 500

class App { // The App class handles the application runtime.
  public:
    int runApp() {
      if(start() == 1) {
        return 1;
      };
      enterLoop();
      shutdown();
      return 0;
    }

  private:  
    SDL_Window* _window;
    SDL_Renderer* _renderer;

  
    int start() {
      SDL_Init(SDL_INIT_VIDEO);
      _window = SDL_CreateWindow("An SDL2 Window",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_HEIGHT,
                                SCREEN_WIDTH,
                                SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
      if(_window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << '\n';
        return 1;
      }
      
      _renderer = SDL_CreateRenderer(_window, -1, 0);
      if(_renderer == NULL) {
        std::cout << "Could not create renderer: " << SDL_GetError() << '\n';
        return 1;
      }
      return 0;
    }
    
    int enterLoop() {
      bool running = true;
      
      while(running == true) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
          if(event.key.keysym.sym == SDLK_q) {
            running = false;
          }
        }
        
        drawWorld();
        SDL_Delay(16);
        
      }

      return 0;
    }
    
    int shutdown() {
      SDL_DestroyRenderer(_renderer);
      SDL_DestroyWindow(_window);
      SDL_Quit();
      return 0;
    }
    
    void drawWorld() {
      drawBackground();
      SDL_RenderPresent(_renderer);
    }
    
    void drawBackground() {
      SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
      SDL_RenderClear(_renderer);
    }
};