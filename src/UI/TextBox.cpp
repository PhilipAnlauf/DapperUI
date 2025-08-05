#include "../../include/DapperUI/TextBox.h"
#include <iostream>

namespace DapperUI
{
		std::function<void()> onClick;

		TextBox::TextBox (int bx, int by, int bw, int bh, int brw)
		{
			x = bx, y = by, w = bw, h = bh, borderWidth = brw;
			rect.x = bx, rect.y = by, rect.h = bh, rect.w = bw;
		}

		void TextBox::setTextColor(int r, int g, int b, int a)
		{
			textColor.r = r, textColor.g = g, textColor.b = b, textColor.a = a;
		}

		void TextBox::setBackGroundColor(int r, int g, int b, int a) { backGroundColor.r = r, backGroundColor.g = g, backGroundColor.b = b, backGroundColor.a = a; }

	    void TextBox::modifyShadow(const int& offsetX, const int& offsetY, const int& sr, const int& sg, const int& sb, const int& sa)
		{
			offX = offsetX;
			offY = offsetY;
			shadowColor.r = sr, shadowColor.g = sg, shadowColor.b = sb, shadowColor.a = sa;
		}

		void TextBox::setText(const int& offsetX, const int& offsetY, const std::string& text, const int& ptsize)
		{
			if (font == nullptr)
			{
				if (TTF_Init() == -1) {
					//std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
					SDL_Quit();
					return;
				}

				font = TTF_OpenFont("fonts/Roboto.ttf", ptsize);
				if (font == NULL) {
					//std::cerr << "TTF_OpenFont failed: " << TTF_GetError() << std::endl;
					TTF_Quit();
					return;
				}
				//std::cout << "Font loaded successfully!" << std::endl;
			}

			boxText = text;
		}

		void TextBox::render(SDL_Renderer* renderer)
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
			if (!boxText.empty())
			{
				const SDL_Color textRenderColor = {textColor.r, textColor.g, textColor.b, textColor.a};

				int wrapLength = w - 2 * padding;
				SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, boxText.c_str(), textRenderColor, wrapLength);
				SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

				int textW = textSurface->w;
				int textH = textSurface->h;

				SDL_Rect textRect = {x, y, textW, textH};

				// textRect.x = x + (w - textW) / 2;
				// textRect.y = y + (h - textH) / 2;

				textRect.x = x + padding;
				textRect.y = y + padding;

				SDL_FreeSurface(textSurface);
				SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
				SDL_DestroyTexture(textTexture);
			}


		}

		void TextBox::handleEvent(const SDL_Event& event)  { }
		void TextBox::update(float deltaTime)  { }
};
