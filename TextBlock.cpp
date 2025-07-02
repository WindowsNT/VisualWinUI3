#include "pch.h"
#include "property.hpp"

class ITEM_TEXTBLOCK : public XITEM
{
public:

	TextBlock X;
	ITEM_TEXTBLOCK()
	{
		ElementName = L"TextBlock";
	}


	virtual void ApplyProperties()
	{
		ApplyPropertiesForText(X.as<TextBlock>(), properties);
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
			auto uip = CreatePropertiesForText<TextBlock>(X.as<TextBlock>(), L"TextBlock");
			for (auto& p : uip)
			{
				p->g = L"TextBlock";
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
		X = TextBlock();
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
		X.Text(L"Hello");
		return X;
	}




	void Select()
	{
	}

	void Unselect()
	{
	}
};


std::shared_ptr<XITEM> CreateXItemTextBlock()
{
	return std::make_shared< ITEM_TEXTBLOCK>();
}
