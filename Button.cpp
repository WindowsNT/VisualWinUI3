#include "pch.h"
#include "property.hpp"

class ITEM_BUTTON : public XITEM
{
public:

	Button X;
	ITEM_BUTTON()
	{
		ElementName = L"Button";
	}


	virtual void ApplyProperties()
	{
		ApplyPropertiesForContent(X.as<Button>(), properties);
		if (!properties.empty())
			properties[0]->S = 1;
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
		if (1)
		{
			auto uip = CreatePropertiesFor(X.as<FrameworkElement>());
			for (auto& p : uip)
			{
				properties.push_back(p);
			}
		}
		if (1)
		{
			auto uip = CreatePropertiesFor(X.as<UIElement>());
			for (auto& p : uip)
			{
				properties.push_back(p);
			}
		}
	}

	virtual winrt::Microsoft::UI::Xaml::UIElement Create() override
	{
		X = Button();
		if (properties.empty())
			LoadProperties();

		X.Tapped([](winrt::Windows::Foundation::IInspectable t, winrt::Microsoft::UI::Xaml::Input::TappedRoutedEventArgs  teh)
			{
				GenericTap(t);
				teh.Handled(true);
			});
		X.RightTapped([](winrt::Windows::Foundation::IInspectable t, winrt::Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs  teh)
			{
				GenericTap(t);
				teh.Handled(true);
			});

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
