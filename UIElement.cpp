#include "pch.h"
#include "property.hpp"

void ApplyPropertiesFor(winrt::Microsoft::UI::Xaml::UIElement e, std::vector <std::shared_ptr<PROPERTY>> props)
{
	if (!e)
		return;
	for (auto& p : props)
	{
		if (p->n == L"Opacity")
		{
			auto op = std::dynamic_pointer_cast<DOUBLE_PROPERTY>(p);
			if (op)
			{
				e.Opacity(op->value);
			}
		}
	}
}



std::vector<std::shared_ptr<PROPERTY>> CreatePropertiesFor(winrt::Microsoft::UI::Xaml::UIElement e)
{
	std::vector<std::shared_ptr<PROPERTY>> p;
	if (!e)
		return p;

	if (1)
	{
		std::shared_ptr<DOUBLE_PROPERTY> op = std::make_shared<DOUBLE_PROPERTY>();
		op->g = L"UIElement";
		op->n = L"Opacity";
		op->mmin = 0.0;
		op->mmax = 1.0;
		op->value = e.Opacity();
		op->def = 1.0;
		p.push_back(op);
	}

	return p;
}
