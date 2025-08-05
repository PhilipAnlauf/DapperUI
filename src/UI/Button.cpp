#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <functional>
#include "../../include/DapperUI/UIElement.h"
#include "../../include/DapperUI/Button.h"
#include <iostream>

namespace DapperUI
{
		Button::Button (int bx, int by, int bw, int bh, int ot)
		{
			x = bx, y = by, w = bw, h = bh, outlineThickness = ot;
			rect.x = bx, rect.y = by, rect.h = bh, rect.w = bw;
		}

		void Button::setTextColor(int r, int g, int b)
		{
			textColor.r = r, textColor.g = g, textColor.b = b;
		}

		void Button::setIdleColor(int r, int g, int b, int a) { idleColor.r = r, idleColor.g = g, idleColor.b = b, idleColor.a = a; }

		void Button::setActiveColor(int r, int g, int b, int a) { activeColor.r = r, activeColor.g = g, activeColor.b = b, activeColor.a = a; }

	    void Button::modifyShadow(const int& offsetX, const int& offsetY, const int& sr, const int& sg, const int& sb, const int& sa)
		{
			offX = offsetX;
			offY = offsetY;
			shadowColor.r = sr, shadowColor.g = sg, shadowColor.b = sb, shadowColor.a = sa;
		}

		void Button::modifyOutline(const int& thickness, const int& otr, const int& otg, const int& otb, const int& ota)
		{
			outlineThickness = thickness;
			outlineColor.r = otr, outlineColor.g = otg, outlineColor.b = otb, outlineColor.a = ota;
		}

		void Button::setText(const int& offsetX, const int& offsetY, const std::string& text, const int& ptsize)
		{
			if (font == nullptr)
			{
				if (TTF_Init() == -1) {
					//std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
					SDL_Quit();
					return;
				}

				// Check absolute or relative path based on your file location
				font = TTF_OpenFont("fonts/Roboto.ttf", ptsize); // Adjust the path accordingly
				if (font == NULL) {
					//std::cerr << "TTF_OpenFont failed: " << TTF_GetError() << std::endl;
					TTF_Quit();
					return;
				}
				//std::cout << "Font loaded successfully!" << std::endl;
			}

			buttonText = text;
		}

		void Button::update(const float deltaTime)
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

		void Button::render(SDL_Renderer* renderer)
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
			SDL_SetRenderDrawColor(renderer,
								   isAnimating ? activeColor.r : idleColor.r,
								   isAnimating ? activeColor.g : idleColor.g,
								   isAnimating ? activeColor.b : idleColor.b,
								   255);

			SDL_RenderFillRect(renderer, &rect);

			//writing text
			if (!buttonText.empty())
			{
				SDL_Color textRenderColor = {textColor.r, textColor.g, textColor.b};
				SDL_Surface* textSurface = TTF_RenderText_Solid(font, buttonText.c_str(), textRenderColor);
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

		void Button::handleEvent(const SDL_Event& event)
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
