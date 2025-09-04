#pragma once
#include "UIElement.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <functional>

namespace DapperUI
{
    class TextBox : public UIElement
{
	private:
		static TTF_Font* font;
		std::string boxText;
		int x,y,w,h;
		SDL_Color backGroundColor = { 255, 255, 255, 255};
		SDL_Color outLineColor = { 0, 0, 0, 255};
		SDL_Color shadowColor = { 0, 0, 0, 128};
		SDL_Color textColor = { 0, 0, 0, 255};
		int offX = 0, offY = 0;
		int borderWidth = 0;
		int padding = 5;

	public:
		std::function<void()> onClick;

		TextBox (int bx, int by, int bw, int bh, int brw=0);

		void setTextColor(int r, int g, int b, int a=255);

		void setBackGroundColor(int r, int g, int b, int a);

	    void modifyShadow(const int& offsetX, const int& offsetY, const int& sr, const int& sg, const int& sb, const int& sa);

		void setText(const int& offsetX=0, const int& offsetY=0, const std::string& text=nullptr, const int& ptsize=24);

		void render(SDL_Renderer* renderer) override;

		void handleEvent(const SDL_Event& event) override;

		void update(float deltaTime) override;
};
}
