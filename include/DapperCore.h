#pragma once
#include <utility>

#include "ElementManager.h"

namespace DapperUI
{
	class DapperCore
	{
		private:
			Uint32 lastTime = SDL_GetTicks();
			float deltaTime = 0.0f;
			int appW, appH;
			std::string appName;
			SDL_Color backgroundColor = {255,255,255,255 };

		public:
			bool running = true;

			static inline ElementManager* elementManager;
			SDL_Window* window;
			static inline SDL_Renderer* renderer;

			void setBackgroundColor(const int r, const int g, const int b)
			{
				backgroundColor.r = r, backgroundColor.g = g, backgroundColor.b = b;
			}

			DapperCore() : appW(800), appH(600), appName("DapperUI Application")
			{
				running = true;
				elementManager = new ElementManager();
				SDL_Init(SDL_INIT_VIDEO);
				window = SDL_CreateWindow(appName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  appW, appH, SDL_WINDOW_SHOWN);
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			}

			DapperCore(const int appW, const int appH, std::string  appN): appW(appW), appH(appH), appName(std::move(appN))
			{
				running = true;
				elementManager = new ElementManager();
				SDL_Init(SDL_INIT_VIDEO);
				window = SDL_CreateWindow(appName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  appW, appH, SDL_WINDOW_SHOWN);
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			}

			static void clearManagers()
			{
				elementManager->deleteObjects();
			}

			~DapperCore()
			{
				delete elementManager;
				elementManager = nullptr;
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				SDL_Quit();
			}

			bool update()
			{
				SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
				SDL_RenderClear(renderer);

				elementManager->renderObjects(renderer);

				SDL_RenderPresent(DapperCore::renderer);

				SDL_Event e;
				while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT)
					{
						running = false;
					}
					elementManager->handleEvents(e);
				}

				const Uint32 currentTime = SDL_GetTicks();
				deltaTime = (currentTime - lastTime) / 500.0f;
				lastTime = currentTime;
				elementManager->updateObjects(deltaTime);

				return running;
			}

			static void render()
			{
				SDL_RenderClear(renderer);
				elementManager->renderObjects(renderer);
				SDL_RenderPresent(renderer);
			}
	};
}