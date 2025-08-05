#include "../../include/DapperUI/Checkbox.h"
#include "../../include/DapperUI/UIElement.h"
#include <iostream>

namespace DapperUI
{
	Checkbox::Checkbox (int bx, int by, int size, int ot)
	{
		x = bx, y = by, w = size, h=size, outlineThickness = ot;
		rect.x = bx, rect.y = by, rect.h = size, rect.w = size;
	}

	void Checkbox::setIdleColor(int r, int g, int b, int a) { idleColor.r = r, idleColor.g = g, idleColor.b = b, idleColor.a = a; }

	void Checkbox::setActiveColor(int r, int g, int b, int a) { activeColor.r = r, activeColor.g = g, activeColor.b = b, activeColor.a = a; }

	void Checkbox::modifyShadow(const int& offsetX, const int& offsetY, const int& sr, const int& sg, const int& sb, const int& sa)
	{
		offX = offsetX;
		offY = offsetY;
		shadowColor.r = sr, shadowColor.g = sg, shadowColor.b = sb, shadowColor.a = sa;
	}

	void Checkbox::modifyOutline(const int& thickness, const int& otr, const int& otg, const int& otb, const int& ota)
	{
		outlineThickness = thickness;
		outlineColor.r = otr, outlineColor.g = otg, outlineColor.b = otb, outlineColor.a = ota;
	}

	void Checkbox::update(const float deltaTime) { };

	void Checkbox::render(SDL_Renderer* renderer)
	{
		//Drawing shadow
		SDL_SetRenderDrawColor(renderer, shadowColor.r, shadowColor.g, shadowColor.b, shadowColor.a);
		SDL_Rect shadowRect = { rect.x + offX - outlineThickness, rect.y + offY - outlineThickness, rect.w + 2 * outlineThickness, rect.h + 2 * outlineThickness };
		SDL_RenderFillRect(renderer, &shadowRect);

		//Drawing outline
		SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
		SDL_Rect outlineRect = { rect.x - outlineThickness, rect.y - outlineThickness, rect.w + 2 * outlineThickness, rect.h + 2 * outlineThickness };
		SDL_RenderFillRect(renderer, &outlineRect);

		//Drawing actual button
		SDL_SetRenderDrawColor(renderer,
							   isAnimating ? activeColor.r : idleColor.r,
							   isAnimating ? activeColor.g : idleColor.g,
							   isAnimating ? activeColor.b : idleColor.b,
							   255);

		SDL_RenderFillRect(renderer, &rect);

	}

	void Checkbox::swapColors()
	{
		const SDL_Color temp = idleColor;
		idleColor = activeColor;
		activeColor = temp;
	}

	void Checkbox::assignBoolean(bool* booleanIN)
	{
		assignedBoolean = booleanIN;
	}

	void Checkbox::handleEvent(const SDL_Event& event)
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