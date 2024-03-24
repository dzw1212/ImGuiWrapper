#pragma once
#include "Text.h"
#include "Button.h"
#include "Window.h"

#include <memory>

class WidgetFactory
{
public:
	template<typename T, typename... Args>
	static std::shared_ptr<Widget> CreateWidget(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
};