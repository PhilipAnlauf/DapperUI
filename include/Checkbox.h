#pragma once

#include "UIElement.h"
#include <SDL2/SDL.h>
#include <functional>

namespace DapperUI
{
    class Checkbox : public UIElement
	{
		private:
			int outlineThickness=2;
			int x=0,y=0,w=0,h=0;
			bool isAnimating = false;
			float animationTimer = 0.0f;
			SDL_Color idleColor = { 255, 255, 255, 255};
			SDL_Color activeColor = { 90, 90, 90, 255};
			SDL_Color shadowColor = { 0, 0, 0, 255};
			SDL_Color outlineColor = { 0, 0, 0, 255};
			bool* assignedBoolean = nullptr;
			int offX = 0, offY = 0;

    		void swapColors();
		public:
			std::function<void()> onClick;

			Checkbox (int bx, int by, int size, int ot=2);

			void setIdleColor(int r, int g, int b, int a);

			void setActiveColor(int r, int g, int b, int a);

			void modifyShadow(const int& offsetX, const int& offsetY, const int& sr, const int& sg, const int& sb, const int& sa);

			void modifyOutline(const int& thickness, const int& otr, const int& otg, const int& otb, const int& ota=255);

			void update(const float deltaTime) override;

			void render(SDL_Renderer* renderer) override;

			void assignBoolean(bool* booleanIN);

			void handleEvent(const SDL_Event& event) override;
	};

}