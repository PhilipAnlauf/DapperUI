#pragma once

#include "UIElement.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <functional>

namespace DapperUI
{
	class ProgressBar : public UIElement
	{
		private:
			TTF_Font* font = nullptr;
			int x,y,w,h;
			bool isAnimating = false;
			float animationTimer = 0.0f;
			SDL_Color backGroundColor = { 120, 120, 120, 255};
			SDL_Color progressColor = { 90, 90, 90, 255};
			SDL_Color shadowColor = { 0, 0, 0, 255};
			SDL_Color outlineColor = { 0, 0, 0, 255};
			int offX = 0, offY = 0;
			int outlineThickness = 0;

			int progressPercentage = 0;

		public:
			std::function<void()> onClick;

			ProgressBar (int bx, int by, int bw, int bh, int ot=0);

			void setBackGroundColor(int r, int g, int b, int a);

			void setProgressColor(int r, int g, int b, int a);

		    void modifyShadow(const int& offsetX, const int& offsetY, const int& sr, const int& sg, const int& sb, const int& sa);

			void increaseByIntPercent(int percentage);

			void modifyOutline(const int& thickness, const int& otr, const int& otg, const int& otb, const int& ota=255);

			void update(const float deltaTime) override;

			void render(SDL_Renderer* renderer) override;

			void handleEvent(const SDL_Event& event) override;
	};
}