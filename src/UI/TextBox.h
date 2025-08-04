#pragma once
#include "UIElement.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <functional>

class TextBox : public UIElement
{
	private:
		TTF_Font* font = nullptr;
		std::string boxText;
		int x,y,w,h;
		SDL_Color backGroundColor = { 255, 255, 255, 255};
		SDL_Color outLineColor = { 0, 0, 0, 255};
		SDL_Color shadowColor = { 0, 0, 0, 128};
		int offX = 0, offY = 0;
		int borderWidth = 0;

	public:
		std::function<void()> onClick;

		TextBox (int bx, int by, int bw, int bh, int brw=0)
		{
			x = bx, y = by, w = bw, h = bh, borderWidth = brw;
			rect.x = bx, rect.y = by, rect.h = bh, rect.w = bw;
		}

		void setBackGroundColor(int r, int g, int b, int a) { backGroundColor.r = r, backGroundColor.g = g, backGroundColor.b = b, backGroundColor.a = a; }

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

				font = TTF_OpenFont("UI/fonts/Roboto.ttf", ptsize);
				if (font == NULL) {
					std::cerr << "TTF_OpenFont failed: " << TTF_GetError() << std::endl;
					TTF_Quit();
					return;
				}
				std::cout << "Font loaded successfully!" << std::endl;
			}

			boxText = text;
		}

		void render(SDL_Renderer* renderer) override
		{
			//Drawing shadow box
			SDL_SetRenderDrawColor(renderer, shadowColor.r, shadowColor.g, shadowColor.b, shadowColor.a);
			SDL_Rect shadowRect = { rect.x + offX, rect.y + offY, rect.w+borderWidth, rect.h+borderWidth };
			SDL_RenderFillRect(renderer, &shadowRect);

			//Drawing "outline" box
			SDL_SetRenderDrawColor(renderer, outLineColor.r, outLineColor.g, outLineColor.b, outLineColor.a);
			SDL_Rect outlineRect = { rect.x - borderWidth, rect.y - borderWidth, rect.w+borderWidth, rect.h+borderWidth };
			SDL_RenderFillRect(renderer, &outlineRect);

			//Drawing the background
			SDL_SetRenderDrawColor(renderer, backGroundColor.r, backGroundColor.g, backGroundColor.b, backGroundColor.a);
			SDL_RenderFillRect(renderer, &rect);

			//writing text
			if (!boxText.empty() && boxText.length() > 0)
			{
				SDL_Color textColor = {255, 255, 255};
				SDL_Surface* textSurface = TTF_RenderText_Solid(font, boxText.c_str(), textColor);
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

		void handleEvent(const SDL_Event& event) override { }
		void update(float deltaTime) override { }
};
