#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <utility>

namespace DapperUI
{
    class UIElement
    {
        public:
            virtual ~UIElement() = default;

            SDL_Rect rect {};
            bool active = true;

            virtual void update(float deltaTime) = 0;
            virtual void render(SDL_Renderer* renderer) = 0;
            virtual void handleEvent(const SDL_Event& event) {}

            std::pair<int, int> getCords() const
            {
                return {rect.x, rect.y};
            }
    };
}
