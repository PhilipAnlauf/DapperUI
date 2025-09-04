#include <SDL2/SDL.h>
#include "../include/UIElement.h"
#include "../include/Rectangle.h"

namespace DapperUI
{
		Rectangle::Rectangle (int bx, int by, int bw, int bh, int ot)
		{
			x = bx, y = by, w = bw, h = bh, outlineThickness = ot;
			rect.x = bx, rect.y = by, rect.h = bh, rect.w = bw;
		}

		void Rectangle::setIdleColor(int r, int g, int b, int a) { idleColor.r = r, idleColor.g = g, idleColor.b = b, idleColor.a = a; }

	    void Rectangle::modifyShadow(const int& offsetX, const int& offsetY, const int& sr, const int& sg, const int& sb, const int& sa)
		{
			offX = offsetX;
			offY = offsetY;
			shadowColor.r = sr, shadowColor.g = sg, shadowColor.b = sb, shadowColor.a = sa;
		}

		void Rectangle::modifyOutline(const int& thickness, const int& otr, const int& otg, const int& otb, const int& ota)
		{
			outlineThickness = thickness;
			outlineColor.r = otr, outlineColor.g = otg, outlineColor.b = otb, outlineColor.a = ota;
		}

		void Rectangle::update(const float deltaTime) {};

		void Rectangle::render(SDL_Renderer* renderer)
		{
			//Drawing button shadow first
			if (offX != 0 && offY != 0)
			{
				SDL_SetRenderDrawColor(renderer, shadowColor.r, shadowColor.g, shadowColor.b, shadowColor.a);
				const SDL_Rect shadowRect = { rect.x + offX, rect.y + offY, rect.w+outlineThickness, rect.h+outlineThickness };
				SDL_RenderFillRect(renderer, &shadowRect);
			}

			if (outlineThickness > 0)
			{
				SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
				const SDL_Rect outlineRect = { rect.x-outlineThickness, rect.y-outlineThickness, rect.w+(2*outlineThickness), rect.h+(2*outlineThickness)};
				SDL_RenderFillRect(renderer, &outlineRect);
			}

			//Drawing actual button
			SDL_SetRenderDrawColor(renderer, idleColor.r, idleColor.g, idleColor.b, idleColor.a);

			SDL_RenderFillRect(renderer, &rect);
		}
};
