#include "pch.h"
#include "property.hpp"

void ApplyPropertiesFor(winrt::Microsoft::UI::Xaml::Controls::Control e, std::vector <std::shared_ptr<PROPERTY>> props)
{
	if (!e)
		return;


	ApplyPropertiesForFont< winrt::Microsoft::UI::Xaml::Controls::Control>(e, props);
	ApplyPropertiesForBackground< winrt::Microsoft::UI::Xaml::Controls::Control>(e,props);
}



std::vector<std::shared_ptr<PROPERTY>> CreatePropertiesFor(winrt::Microsoft::UI::Xaml::Controls::Control e)
{
	std::vector<std::shared_ptr<PROPERTY>> p;
	if (!e)
		return p;

	if (1)
	{
		auto p1 = CreatePropertiesForFont< winrt::Microsoft::UI::Xaml::Controls::Control>(e);
		for (auto& pp : p1)
			p.push_back(pp);
	}
	if (1)
	{
		auto p1 = CreatePropertiesForBackground< winrt::Microsoft::UI::Xaml::Controls::Control>(e);
		for (auto& pp : p1)
		{
			pp->g = L"Control";
			p.push_back(pp);
		}
	}

	return p;
}
