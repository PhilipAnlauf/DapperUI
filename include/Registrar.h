#pragma once
#include "DapperCore.h"
#include <memory>
#include <utility>

//Function called when a new element is created
//TODO: Add to dapper core or element manager

namespace DapperUI
{
    template <typename T, typename... Args>
    T* CreateUIElement(Args&&... args)
    {
        T* element = new T(std::forward<Args>(args)...);
        DapperCore::elementManager->addElement(std::unique_ptr<UIElement>(element));
        return element;
    }
}
