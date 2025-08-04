#pragma once
#include "UIElement.h"
#include <string>
#include <SDL2/SDL.h>
#include <functional>

class Checkbox : public UIElement
{
	private:
		int outlineThickness;
		int x,y,w,h;
		bool isAnimating = false;
		float animationTimer = 0.0f;
		SDL_Color idleColor = { 255, 255, 255, 255};
		SDL_Color activeColor = { 90, 90, 90, 255};
		SDL_Color shadowColor = { 0, 0, 0, 255};
		SDL_Color outlineColor = { 0, 0, 0, 255};
		bool* assignedBoolean;
		int offX, offY;

	public:
		std::function<void()> onClick;

		Checkbox (int bx, int by, int size, int ot=2)
		{
			x = bx, y = by, w = size, h=size, outlineThickness = ot;
			rect.x = bx, rect.y = by, rect.h = size, rect.w = size;
		}

		void setIdleColor(int r, int g, int b, int a) { idleColor.r = r, idleColor.g = g, idleColor.b = b, idleColor.a = a; }

		void setActiveColor(int r, int g, int b, int a) { activeColor.r = r, activeColor.g = g, activeColor.b = b, activeColor.a = a; }

		void modifyShadow(const int& offsetX, const int& offsetY, const int& sr, const int& sg, const int& sb, const int& sa)
		{
			offX = offsetX;
			offY = offsetY;
			shadowColor.r = sr, shadowColor.g = sg, shadowColor.b = sb, shadowColor.a = sa;
		}

		void modifyOutline(const int& thickness, const int& otr, const int& otg, const int& otb, const int& ota=255)
		{
			outlineThickness = thickness;
			outlineColor.r = otr, outlineColor.g = otg, outlineColor.b = otb, outlineColor.a = ota;
		}

		void update(const float deltaTime) override { };

		void render(SDL_Renderer* renderer) override
		{
			//Drawing shadow
			SDL_SetRenderDrawColor(renderer, shadowColor.r, shadowColor.g, shadowColor.b, shadowColor.a);
			SDL_Rect shadowRect = { rect.x + offX - outlineThickness, rect.y + offY - outlineThickness, rect.w + 2 * outlineThickness, rect.h + 2 * outlineThickness };
			SDL_RenderFillRect(renderer, &shadowRect);

			//Drawing outline
			SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
			SDL_Rect outlineRect = { rect.x - outlineThickness, rect.y - outlineThickness, rect.w + 2 * outlineThickness, rect.h + 2 * outlineThickness };
			SDL_RenderFillRect(renderer, &outlineRect);

			//Drawing actual button
			SDL_SetRenderDrawColor(renderer,
								   isAnimating ? activeColor.r : idleColor.r,
								   isAnimating ? activeColor.g : idleColor.g,
								   isAnimating ? activeColor.b : idleColor.b,
								   255);

			SDL_RenderFillRect(renderer, &rect);

		}

		void swapColors()
		{
			const SDL_Color temp = idleColor;
			idleColor = activeColor;
			activeColor = temp;
		}

		void assignBoolean(bool* booleanIN)
		{
			assignedBoolean = booleanIN;
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
				swapColors();
				if (assignedBoolean != nullptr)
				{
					*assignedBoolean = !*assignedBoolean;
				}
			}
		}
};
