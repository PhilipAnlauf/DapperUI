#include "../include/TextBox.h"

namespace DapperUI
{
		TTF_Font* TextBox::font = nullptr;

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
			TTF_Init();
			boxText = text;
			if (!font)
			{
				font = TTF_OpenFont("Roboto.ttf", ptsize);
				if (!font) {
					//std::cerr << "Failed to open font: " << TTF_GetError() << std::endl;
					return;
				} else {
					//std::cout << "Font loaded successfully!" << std::endl;
				}
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

			if (!boxText.empty() && font != nullptr)
			{
				const SDL_Color textRenderColor = {textColor.r, textColor.g, textColor.b, textColor.a};

				SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, boxText.c_str(), textRenderColor, w - 2 * padding);
				SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
				SDL_FreeSurface(textSurface);

				SDL_Rect textRect = {x+padding, y+padding, 0, 0};

				SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

				SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
				SDL_DestroyTexture(textTexture);
			}


		}

		void TextBox::handleEvent(const SDL_Event& event)  { }
		void TextBox::update(float deltaTime)  { }
};
