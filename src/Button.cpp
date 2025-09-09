#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <functional>
#include "../include/UIElement.h"
#include "../include/Button.h"
#include <iostream>

namespace DapperUI
{
		Button::Button (const int bx, const int by, const int bw, const int bh, const int ot)
		{
			x = bx, y = by, w = bw, h = bh, outlineThickness = ot;
			rect.x = bx, rect.y = by, rect.h = bh, rect.w = bw;
		}

		void Button::setTextColor(int r, int g, int b)
		{
			textColor.r = r, textColor.g = g, textColor.b = b;
		}

		void Button::setIdleColor(const int r, const int g, const int b, const int a) { idleColor.r = r, idleColor.g = g, idleColor.b = b, idleColor.a = a; }

		void Button::setActiveColor(const int r, const int g, const int b, const int a) { activeColor.r = r, activeColor.g = g, activeColor.b = b, activeColor.a = a; }

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
			TTF_Init();
			buttonText = text;
			if (!font)
			{
				font = TTF_OpenFont("Roboto.ttf", ptsize);
				if (!font) {
					std::cerr << "Failed to open font: " << TTF_GetError() << std::endl;
					return;
				} else {
					std::cout << "Font loaded successfully!" << std::endl;
				}
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
			if (!buttonText.empty() && font != nullptr)
			{
				const SDL_Color textRenderColor = {textColor.r, textColor.g, textColor.b, textColor.a};

				SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, buttonText.c_str(), textRenderColor, w - 2);
				SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
				SDL_FreeSurface(textSurface);

				int textW = textSurface->w;
				int textH = textSurface->h;
				SDL_Rect textRect = {x, y, textW, textH};
				textRect.x = x + (w - textW) / 2;
				textRect.y = y + (h - textH) / 2;

				SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

				SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
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
