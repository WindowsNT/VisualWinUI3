#include "pch.h"
#include "property.hpp"

class ITEM_BUTTON : public XITEM
{
public:

	Button X;
	virtual winrt::Windows::Foundation::IInspectable XX() override
	{
		return X;
	}
	ITEM_BUTTON()
	{
		ElementName = L"Button";
	}


	virtual void ApplyProperties()
	{
		ApplyPropertiesForContent(X.as<Button>(), properties);
		ApplyPropertiesFor(X.as<Control>(), properties);
		ApplyPropertiesFor(X.as<UIElement>(), properties);
		ApplyPropertiesFor(X.as<FrameworkElement>(), properties);
	}


	virtual void LoadProperties() override
	{
		properties.clear();
		if (1)
		{
			auto uip = CreatePropertiesForContent(X.as<Button>(), L"Button");
			for (auto& p : uip)
			{
				p->g = L"Button";
				properties.push_back(p);
			}
		}
		AddPropertySet<Control>();
		AddPropertySet<FrameworkElement>();
		AddPropertySet<UIElement>();
	}

	virtual winrt::Microsoft::UI::Xaml::UIElement Create(int ForWhat) override
	{
		X = Button();
		if (properties.empty())
			LoadProperties();

		if (ForWhat == 0)
		{
			AllTap(X);
		}

		X.Tag(box_value((long long)this));
		X.Content(winrt::box_value(L"Button"));
		xb = std::make_shared<winrt::Microsoft::UI::Xaml::Media::Brush>(X.Background());
		return X;
	}

	std::shared_ptr<winrt::Microsoft::UI::Xaml::Media::Brush> xb;



	void Select()
	{
		X.Background(SolidColorBrush(Colors::Red()));
	}

	void Unselect()
	{
		if (xb)
			X.Background(*xb);
	}
};


std::shared_ptr<XITEM> CreateXItemButton()
{
	return std::make_shared< ITEM_BUTTON>();
}
