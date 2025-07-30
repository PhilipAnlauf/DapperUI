#pragma once
#include "UIElement.h"
#include <string>
#include <SDL2/SDL.h>
#include <functional>

class Checkbox : public UIElement
{
	private:
		int radius;
		int outlineThickness;
		int x,y,w,h;
		bool isAnimating = false;
		float animationTimer = 0.0f;
		SDL_Color idleColor = { 255, 255, 255, 255};
		SDL_Color activeColor = { 90, 90, 90, 255};
		SDL_Color shadowColor = { 0, 0, 0, 255};
		bool* assignedBoolean;

	public:
		std::function<void()> onClick;

		Checkbox (int bx, int by, int size, int br=10, int ot=2)
		{
			x = bx, y = by, w = size, h=size, radius = br, outlineThickness = ot;
			rect.x = bx, rect.y = by, rect.h = size, rect.w = size;
		}

		void setIdleColor(int r, int g, int b, int a) { idleColor.r = r, idleColor.g = g, idleColor.b = b, idleColor.a = a; }

		void setActiveColor(int r, int g, int b, int a) { activeColor.r = r, activeColor.g = g, activeColor.b = b, activeColor.a = a; }

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

		static void FillCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius)
		{
			for (int y = -radius; y <= radius; y++)
			{
				int dx = (int)sqrt(radius * radius - y * y);
				int x1 = centerX - dx;
				int x2 = centerX + dx;

				SDL_RenderDrawLine(renderer, x1, centerY + y, x2, centerY + y);
			}
		}

		void render(SDL_Renderer* renderer) override
		{
			//Drawing outline first
			SDL_SetRenderDrawColor(renderer, shadowColor.r, shadowColor.g, shadowColor.b, shadowColor.a);
			if (radius > 0)
			{
				int outerRadius = radius + outlineThickness;
				int outerX = x - outlineThickness;
				int outerY = y - outlineThickness;
				int outerW = w + 2 * outlineThickness;
				int outerH = h + 2 * outlineThickness;

				// Draw filled corner circles for outline
				FillCircle(renderer, outerX + outerRadius, outerY + outerRadius, outerRadius);
				FillCircle(renderer, outerX + outerW - outerRadius, outerY + outerRadius, outerRadius);
				FillCircle(renderer, outerX + outerRadius, outerY + outerH - outerRadius, outerRadius);
				FillCircle(renderer, outerX + outerW - outerRadius, outerY + outerH - outerRadius, outerRadius);

				// Draw rectangles to fill between corners (outline)
				SDL_Rect top = { outerX + outerRadius, outerY, outerW - 2 * outerRadius, outerRadius };
				SDL_Rect bottom = { outerX + outerRadius, outerY + outerH - outerRadius, outerW - 2 * outerRadius, outerRadius };
				SDL_Rect left = { outerX, outerY + outerRadius, outerRadius, outerH - 2 * outerRadius };
				SDL_Rect right = { outerX + outerW - outerRadius, outerY + outerRadius, outerRadius, outerH - 2 * outerRadius };
				SDL_Rect center = { outerX + outerRadius, outerY + outerRadius, outerW - 2 * outerRadius, outerH - 2 * outerRadius };

				SDL_RenderFillRect(renderer, &top);
				SDL_RenderFillRect(renderer, &bottom);
				SDL_RenderFillRect(renderer, &left);
				SDL_RenderFillRect(renderer, &right);
				SDL_RenderFillRect(renderer, &center);
			}
			else
			{
				SDL_Rect shadowRect = { rect.x - outlineThickness, rect.y - outlineThickness, rect.w + 2 * outlineThickness, rect.h + 2 * outlineThickness };
				SDL_RenderFillRect(renderer, &shadowRect);
			}

			//Drawing actual button
			SDL_SetRenderDrawColor(renderer,
								   isAnimating ? activeColor.r : idleColor.r,
								   isAnimating ? activeColor.g : idleColor.g,
								   isAnimating ? activeColor.b : idleColor.b,
								   255);

			if (radius > 0)
			{
				FillCircle(renderer, x+radius, y+radius, radius);
				FillCircle(renderer, x+w-radius, y+radius, radius);
				FillCircle(renderer, x+radius, y+h-radius, radius);
				FillCircle(renderer, x+w-radius, y+h-radius, radius);

				const SDL_Rect vertical = { x + radius, y, w - 2 * radius, h };
				SDL_RenderFillRect(renderer, &vertical);

				const SDL_Rect horizontal = { x, y + radius, w, h - 2 * radius };
				SDL_RenderFillRect(renderer, &horizontal);
			}
			else
			{
				SDL_RenderFillRect(renderer, &rect);
			}

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
