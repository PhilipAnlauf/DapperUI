#pragma once
#include "UIElement.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <functional>

class Button : public UIElement
{
	private:
		TTF_Font* font = nullptr;
		std::string buttonText;
		int radius = 0;
		int x,y,w,h;
		bool isAnimating = false;
		float animationTimer = 0.0f;
		SDL_Color idleColor = { 120, 120, 120, 255};
		SDL_Color activeColor = { 90, 90, 90, 255};
		SDL_Color shadowColor = { 0, 0, 0, 255};
		int offX = 0, offY = 0;

	public:
		std::function<void()> onClick;

		Button (int bx, int by, int bw, int bh, int br=0)
		{
			x = bx, y = by, w = bw, h = bh, radius = br;
			rect.x = bx, rect.y = by, rect.h = bh, rect.w = bw;
		}

		void setIdleColor(int r, int g, int b, int a) { idleColor.r = r, idleColor.g = g, idleColor.b = b, idleColor.a = a; }

		void setActiveColor(int r, int g, int b, int a) { activeColor.r = r, activeColor.g = g, activeColor.b = b, activeColor.a = a; }

	    void modifyShadow(const int& offsetX, const int& offsetY, const int& sr, const int& sg, const int& sb, const int& sa)
		{
			offX = offsetX;
			offY = offsetY;
			shadowColor.r = sr, shadowColor.g = sg, shadowColor.b = sb, shadowColor.a = sa;
		}

		void setText(const int& offsetX=0, const int& offsetY=0, const std::string& text=nullptr, const int& ptsize=24)
		{
			if (font == nullptr)
			{
				if (TTF_Init() == -1) {
					std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
					SDL_Quit();
					return;
				}

				// Check absolute or relative path based on your file location
				font = TTF_OpenFont("UI/fonts/Roboto.ttf", ptsize); // Adjust the path accordingly
				if (font == NULL) {
					std::cerr << "TTF_OpenFont failed: " << TTF_GetError() << std::endl;
					TTF_Quit();
					return;
				}
				std::cout << "Font loaded successfully!" << std::endl;
			}

			buttonText = text;
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

		static void DrawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius)
		{
			int x = radius;
			int y = 0;
			int err = 0;

			while (x >= y)
			{
				SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
				SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
				SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
				SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
				SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
				SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
				SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
				SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);

				y += 1;
				if (err <= 0)
				{
					err += 2 * y + 1;
				}
				if (err > 0)
				{
					x -= 1;
					err -= 2 * x + 1;
				}
			}
		}

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
			//Drawing button shadow first
			SDL_SetRenderDrawColor(renderer, shadowColor.r, shadowColor.g, shadowColor.b, shadowColor.a);
			if (radius > 0)
			{
				FillCircle(renderer, x+radius+offX, y+radius+offY, radius);
				FillCircle(renderer, x+w-radius+offX, y+radius+offY, radius);
				FillCircle(renderer, x+radius+offX, y+h-radius+offY, radius);
				FillCircle(renderer, x+w-radius+offX, y+h-radius+offY, radius);

				const SDL_Rect shadowVerticalRect = { x + radius+offX, y + offY, w - 2 * radius, h };
				SDL_RenderFillRect(renderer, &shadowVerticalRect);

				const SDL_Rect shadowHorizontalRect = { x + offX, y + radius + offY, w, h - 2 * radius };
				SDL_RenderFillRect(renderer, &shadowHorizontalRect);
			}
			else
			{
				SDL_Rect shadowRect = { rect.x + offX, rect.y + offY, rect.w, rect.h };
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

			//writing text
			if (!buttonText.empty() && buttonText.length() > 0)
			{
				SDL_Color textColor = {255, 255, 255};
				SDL_Surface* textSurface = TTF_RenderText_Solid(font, buttonText.c_str(), textColor);
				SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

				int textW = textSurface->w;
				int textH = textSurface->h;

				SDL_Rect textRect = {x, y, textW, textH};

				textRect.x = x + (w - textW) / 2;
				textRect.y = y + (h - textH) / 2;

				SDL_FreeSurface(textSurface);
				SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
				SDL_DestroyTexture(textTexture);
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
