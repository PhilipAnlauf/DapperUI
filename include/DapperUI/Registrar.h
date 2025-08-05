#pragma once
#include "DapperCore.h"
#include <memory>
#include <utility>

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
