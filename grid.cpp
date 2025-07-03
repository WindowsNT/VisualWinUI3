#include "pch.h"
#include "property.hpp"

using namespace winrt::Microsoft::UI::Xaml::Controls;
class ITEM_GRID : public XITEM
{
public:

	Grid X;
	virtual winrt::Windows::Foundation::IInspectable XX() override
	{
		return X;
	}

	ITEM_GRID()
	{
		ElementName = L"Grid";
	}


	virtual void ApplyProperties()
	{
		ApplyPropertiesFor(X.as<UIElement>(), properties);
		ApplyPropertiesFor(X.as<FrameworkElement>(), properties);
		ApplyPropertiesFor(X.as<Panel>(), properties);
	}

	virtual void LoadProperties() override
	{
		properties.clear();
		AddPropertySet<Panel>();
		AddPropertySet<FrameworkElement>();
		AddPropertySet<UIElement>();
	}

	virtual winrt::Microsoft::UI::Xaml::UIElement Create(int ForWhat, XITEM* par) override
	{
		X = Grid();
		the_par = par;
		if (properties.empty())
			LoadProperties();
		AddGridPropertiesIf<Grid>(par);

		if (ForWhat == 0)
		{
			AllTap(X);
		}

		X.Tag(box_value((long long)this));
		if (ForWhat == 0)
			X.Background(SolidColorBrush(Colors::Transparent()));
		return X;
	}

	void Select()
	{
		X.Background(SolidColorBrush(Colors::Red()));
	}

	void Unselect()
	{
		X.Background(SolidColorBrush(Colors::Transparent()));
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
