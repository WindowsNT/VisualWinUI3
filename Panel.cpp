#include "pch.h"
#include "property.hpp"

void ApplyPropertiesFor(winrt::Microsoft::UI::Xaml::Controls::Panel e, std::vector <std::shared_ptr<PROPERTY>> props)
{
	if (!e)
		return;
	for (auto& p : props)
	{
		p;
	}
}


std::vector<std::shared_ptr<PROPERTY>> CreatePropertiesFor(winrt::Microsoft::UI::Xaml::Controls::Panel e)
{
	std::vector<std::shared_ptr<PROPERTY>> p;
	if (!e)
		return p;


	return p;
}
