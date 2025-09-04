#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <functional>
#include "UIElement.h"

namespace DapperUI
{
    class Button : public UIElement
    {
    private:
        TTF_Font* font = nullptr;
        std::string buttonText;
        int x,y,w,h;
        bool isAnimating = false;
        float animationTimer = 0.0f;
        SDL_Color idleColor = { 120, 120, 120, 255};
        SDL_Color activeColor = { 90, 90, 90, 255};
        SDL_Color shadowColor = { 0, 0, 0, 255};
        SDL_Color outlineColor = { 0, 0, 0, 255};
        SDL_Color textColor = { 0, 0, 0, 255};
        int offX = 0, offY = 0;
        int outlineThickness = 0;
    public:
        std::function<void()> onClick;

        Button(int bx, int by, int bw, int bh, int ot = 0);

        void setTextColor(int r, int g, int b);
        void setIdleColor(int r, int g, int b, int a);
        void setActiveColor(int r, int g, int b, int a);
        void modifyShadow(const int& offsetX, const int& offsetY, const int& sr, const int& sg, const int& sb, const int& sa);
        void modifyOutline(const int& thickness, const int& otr, const int& otg, const int& otb, const int& ota=255);
        void setText(const int& offsetX=0, const int& offsetY=0, const std::string& text="", const int& ptsize=24);
        void update(const float deltaTime);
        void render(SDL_Renderer* renderer);
        void handleEvent(const SDL_Event& event);
    };
}