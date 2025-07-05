#include "pch.h"
#include "property.hpp"

using namespace winrt::Microsoft::UI::Xaml::Controls;
class ITEM_GRID : public XITEM_Panel
{
public:

	ITEM_GRID()
	{
		ElementName = L"Grid";
		X = winrt::Microsoft::UI::Xaml::Controls::Grid();
	}


	virtual void ApplyProperties()
	{
		XITEM_Panel::ApplyProperties();
	}

	virtual std::vector<std::shared_ptr<PROPERTY>> CreateProperties() override
	{
		properties = XITEM_Panel::CreateProperties();
		return properties;
	}

	virtual winrt::Microsoft::UI::Xaml::UIElement Create(int ForWhat, XITEM* par) override
	{
		X = Grid();
		the_par = par;
		if (properties.empty())
			properties = CreateProperties();
		AddGridPropertiesIf<Grid>(par);

		if (ForWhat == 0)
		{
			AllTap(X);
		}

		auto b = X.try_as<Grid>();
		b.Tag(box_value((long long)this));
		if (ForWhat == 0)
			b.Background(SolidColorBrush(Colors::Transparent()));
		return b;
	}

};

std::shared_ptr<XITEM> CreateXItemGrid()
{
	return std::make_shared< ITEM_GRID>();
}

bool ISXItemGrid(XITEM* xit)
{
	if (!xit)
		return false;
	return dynamic_cast<ITEM_GRID*>(xit) != nullptr;
}
