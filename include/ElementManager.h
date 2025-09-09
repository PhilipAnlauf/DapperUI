#pragma once
#include <algorithm>
#include <vector>
#include <memory>
#include <SDL2/SDL_events.h>
#include "UIElement.h"
#include <iostream>

class ElementManager
{
	private:
		std::vector<std::unique_ptr<DapperUI::UIElement>> elements{};
	public:

		static SDL_DisplayMode getDisplayModeDimensions()
		{
			SDL_DisplayMode mode;
			if (SDL_GetDesktopDisplayMode(0, &mode) != 0)
			{
				std::cout << "Error getting screen dimensions: " << SDL_GetError() << std::endl;
				mode.w = 1920;
				mode.h = 1080;
				return mode;
			}
			return mode;
		}

		void addElement(std::unique_ptr<DapperUI::UIElement> object)
		{
			elements.push_back(std::move(object));
		}

		void updateObjects(const float deltaTime) const
		{
			for (const auto& object : elements)
			{
				object->update(deltaTime);
			}
		}

		void renderObjects(SDL_Renderer* renderer) const
		{
			for(const auto& object : elements)
			{
				auto [x,y] = object->getCords();
				SDL_DisplayMode mode = getDisplayModeDimensions();
				if (x >= 0 && y >= 0 && x + object->rect.w <= mode.w && y + object->rect.h <= mode.h)
				{
					object->render(renderer);
				}
			}
		}

		void deleteObjects()
		{
			elements.clear();
		}

		void handleEvents(const SDL_Event& event) const
		{
			for (auto& object : elements)
			{
				object->handleEvent(event);
			}
		}
};