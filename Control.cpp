#include "pch.h"
#include "property.hpp"

void ApplyPropertiesFor(winrt::Microsoft::UI::Xaml::Controls::Control e, std::vector <std::shared_ptr<PROPERTY>> props)
{
	if (!e)
		return;


	ApplyPropertiesForFont< winrt::Microsoft::UI::Xaml::Controls::Control>(e, props);
	ApplyPropertiesForBackground< winrt::Microsoft::UI::Xaml::Controls::Control>(e, props);
	ApplyPropertiesForForeground< winrt::Microsoft::UI::Xaml::Controls::Control>(e,props);

	for (auto& p : props)
	{
		if (p->n == L"IsEnabled")
		{
			auto op = std::dynamic_pointer_cast<LIST_PROPERTY>(p);
			if (op)
			{
				e.IsEnabled((bool)op->SelectedIndex);
			}
		}
	}

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
	if (1)
	{
		auto p1 = CreatePropertiesForForeground< winrt::Microsoft::UI::Xaml::Controls::Control>(e);
		for (auto& pp : p1)
		{
			pp->g = L"Control";
			p.push_back(pp);
		}
	}	

	if (1)
	{
		std::shared_ptr<LIST_PROPERTY> op = std::make_shared<LIST_PROPERTY>();
		op->g = L"Control";
		op->n = L"IsEnabled";
		op->Items = { L"False", L"True" };
		op->DefaultIndex = 1;
		op->SelectedIndex = 1;
		p.push_back(op);

	}

	return p;
}
