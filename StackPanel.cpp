#include "pch.h"
#include "property.hpp"

using namespace winrt::Microsoft::UI::Xaml::Controls;
class ITEM_STACKPANEL : public XITEM_Panel
{
public:


	ITEM_STACKPANEL()
	{
		ElementName = L"StackPanel";
		X = winrt::Microsoft::UI::Xaml::Controls::StackPanel();
	}


	virtual void ApplyProperties()
	{
		XITEM_Panel::ApplyProperties();
		auto e = X.try_as<StackPanel>();
		if (!e)
			return;
		for (auto& p : properties)
		{
			if (p->n == L"Orientation")
			{
				auto op = std::dynamic_pointer_cast<LIST_PROPERTY>(p);
				if (op)
				{
					e.Orientation((winrt::Microsoft::UI::Xaml::Controls::Orientation)op->SelectedIndex);
				}
			}
		}
	}

	virtual std::vector<std::shared_ptr<PROPERTY>> CreateProperties() override
	{
		properties.clear();
		if (1)
		{
			if (1)
			{
				std::shared_ptr<LIST_PROPERTY> op = std::make_shared<LIST_PROPERTY>();
				op->g = L"StackPanel";
				op->n = L"Orientation";
				op->Items = { L"Vertical", L"Horizontal" };
				op->DefaultIndex = 0;
				properties.push_back(op);

			}
		}

		auto p2 = XITEM_Panel::CreateProperties();
		for (auto& p : p2)
			properties.push_back(p);
		return properties;
	}

	virtual winrt::Microsoft::UI::Xaml::UIElement Create(int ForWhat, XITEM* par) override
	{
		X = StackPanel();
		the_par = par;
		if (properties.empty())
			properties = CreateProperties();
		AddGridPropertiesIf<StackPanel>(par);

		if (ForWhat == 0)
		{
			AllTap(X);
		}

		auto b = X.try_as<StackPanel>();
		b.Tag(box_value((long long)this));
		if (ForWhat == 0)
			b.Background(SolidColorBrush(Colors::Transparent()));
		return b;
	}

};

std::shared_ptr<XITEM> CreateXItemStackPanel()
{
	return std::make_shared< ITEM_STACKPANEL>();
}

bool ISXItemStackPanel(XITEM* xit)
{
	if (!xit)
		return false;
	return dynamic_cast<ITEM_STACKPANEL*>(xit) != nullptr;
}
