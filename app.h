#include <algorithm>
#include <iostream>
#include <SDL2/SDL.h>
#include "neural.h"
#include "timer.h"

#define SCREEN_HEIGHT 500
#define SCREEN_WIDTH 500

class App { // The App class handles the application runtime.
    public:
        int runApp() {
            if (start() == 1) {
                return 1;
            };
            enterLoop();
            shutdown();
            return 0;
        }

    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        NeuralNetwork *_neural;
        Core::Timer *_timer;


        int start() {
            _timer = new Core::Timer();
            SDL_Init(SDL_INIT_VIDEO);
            _window = SDL_CreateWindow("An SDL2 Window",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SCREEN_HEIGHT,
                                       SCREEN_WIDTH,
                                       SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
            if (_window == NULL) {
                std::cout << "Could not create window: " << SDL_GetError() << '\n';
                return 1;
            }

            _renderer = SDL_CreateRenderer(_window, -1, 0);
            if (_renderer == NULL) {
                std::cout << "Could not create renderer: " << SDL_GetError() << '\n';
                return 1;
            }
            //std::vector<int> nodeLayerSizes = { 2, 256, 256, 256, 3 };
            std::vector<int> nodeLayerSizes = {2, 32, 16, 8, 3};
            _neural = new NeuralNetwork(0.05, nodeLayerSizes);
            return 0;
        }

        int enterLoop() {
            bool running = true;

            while (running == true) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    if (event.key.keysym.sym == SDLK_q) {
                        running = false;
                    }
                }

                drawWorld();
                // NeuralNetwork* tmp = _neural;
                //  _neural = new NeuralNetwork(tmp);
                //  delete tmp;
            }

            double elapsed = _timer->Elapsed_Seconds();
            std::cout << "Time: " << elapsed << std::fixed << "    (" << double(SCREEN_HEIGHT * SCREEN_WIDTH) / elapsed << " per second)\n";
            return 0;
        }

        int shutdown() {
            delete _neural;
            SDL_DestroyRenderer(_renderer);
            SDL_DestroyWindow(_window);
            SDL_Quit();
            return 0;
        }

        void drawWorld() {
            drawBackground();
            drawPoints();
            SDL_RenderPresent(_renderer);
        }

        void drawBackground() {
            SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
            SDL_RenderClear(_renderer);
        }

        void drawPoints() {
            for (int y = 0; y < SCREEN_HEIGHT; y++) {
                for (int x = 0; x < SCREEN_WIDTH; x++) {
                    drawPoint(x, y);
                }
            }
        }

        void drawPoint(int x, int y) {
            std::vector<double> inputs;
            inputs.push_back((double)(x - 128) / (double)SCREEN_WIDTH);
            inputs.push_back((double)(y - 128) / (double)SCREEN_HEIGHT);
            _neural->calculateOutputValues(inputs);
            std::vector<double> outputs = _neural->getOutputValues();
            int r = floor(outputs[0] * 256);
            int g = floor(outputs[1] * 256);
            int b = floor(outputs[2] * 256);
            SDL_SetRenderDrawColor(_renderer, r, g, b, 255);
            SDL_RenderDrawPoint(_renderer, x, y);
        }
};