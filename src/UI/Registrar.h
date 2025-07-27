#pragma once
#include "../Core/DapperCore.h"
#include "../UI/UIElement.h"
#include <memory>
#include <utility>

template <typename T, typename... Args>
T* CreateUIElement(Args&&... args)
{
	T* element = new T(std::forward<Args>(args)...);
	DapperCore::elementManager->addElement(std::unique_ptr<UIElement>(element));
	return element;
}