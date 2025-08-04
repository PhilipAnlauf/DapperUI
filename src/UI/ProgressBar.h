#pragma once
#include "UIElement.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <functional>

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

		ProgressBar (int bx, int by, int bw, int bh, int ot=0)
		{
			x = bx, y = by, w = bw, h = bh, outlineThickness = ot;
			rect.x = bx, rect.y = by, rect.h = bh, rect.w = bw;
		}

		void setBackGroundColor(int r, int g, int b, int a) { backGroundColor.r = r, backGroundColor.g = g, backGroundColor.b = b, backGroundColor.a = a; }

		void setProgressColor(int r, int g, int b, int a) { progressColor.r = r, progressColor.g = g, progressColor.b = b, progressColor.a = a; }

	    void modifyShadow(const int& offsetX, const int& offsetY, const int& sr, const int& sg, const int& sb, const int& sa)
		{
			offX = offsetX;
			offY = offsetY;
			shadowColor.r = sr, shadowColor.g = sg, shadowColor.b = sb, shadowColor.a = sa;
		}

		void increaseByIntpercent(int percentage)
		{
			progressPercentage += percentage;
		}

		void modifyOutline(const int& thickness, const int& otr, const int& otg, const int& otb, const int& ota=255)
		{
			outlineThickness = thickness;
			outlineColor.r = otr, outlineColor.g = otg, outlineColor.b = otb, outlineColor.a = ota;
		}

		void update(const float deltaTime) override
		{
			if (isAnimating)
			{
				animationTimer += deltaTime;
				if (animationTimer >= 0.25f)
				{
					isAnimating = false;
					if (onClick) onClick();
				}
			}
		};

		void render(SDL_Renderer* renderer) override
		{
			//Drawing button shadow first
			if (offX != 0 && offY != 0)
			{
				SDL_SetRenderDrawColor(renderer, shadowColor.r, shadowColor.g, shadowColor.b, shadowColor.a);
				const SDL_Rect shadowRect = { rect.x + offX, rect.y + offY, rect.w+outlineThickness, rect.h+outlineThickness };
				SDL_RenderFillRect(renderer, &shadowRect);
			}

			//Drawing outline
			if (outlineThickness > 0)
			{
				SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
				const SDL_Rect outlineRect = { rect.x-outlineThickness, rect.y-outlineThickness, rect.w+(2*outlineThickness), rect.h+(2*outlineThickness)};
				SDL_RenderFillRect(renderer, &outlineRect);
			}

			//Drawing background
			SDL_SetRenderDrawColor(renderer, backGroundColor.r, backGroundColor.g, backGroundColor.b, 255);
			SDL_RenderFillRect(renderer, &rect);

			if (progressPercentage > 0)
			{
				SDL_Rect progressRect;
				SDL_SetRenderDrawColor(renderer, progressColor.r, progressColor.g, progressColor.b, progressColor.a);
				if (progressPercentage >= 100)
				{
					progressRect = { rect.x, rect.y, rect.w, rect.h};
				}
				else { progressRect = { rect.x, rect.y, ((progressPercentage*rect.w)/100), rect.h}; }

				SDL_RenderFillRect(renderer, &progressRect);
			}
		}

		void handleEvent(const SDL_Event& event) override
		{
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			const SDL_Point mousePos = { mouseX, mouseY };

			if (const bool isMouseTouching = SDL_PointInRect(&mousePos, &rect); isMouseTouching && event.type == SDL_MOUSEBUTTONDOWN && !isAnimating)
			{
				isAnimating = true;
				animationTimer = 0.0f;
			}
		}
};
