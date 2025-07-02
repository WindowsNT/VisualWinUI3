#include "pch.h"
#include "property.hpp"

using namespace winrt::Microsoft::UI::Xaml::Controls;
class ITEM_STACKPANEL : public XITEM
{
public:

	StackPanel X;
	ITEM_STACKPANEL()
	{
		ElementName = L"StackPanel";
	}


	virtual void ApplyProperties()
	{
		ApplyPropertiesFor(X.as<UIElement>(), properties);
		ApplyPropertiesFor(X.as<FrameworkElement>(), properties);
		ApplyPropertiesFor(X.as<Panel>(), properties);
		for (auto& p : properties)
		{
			if (p->n == L"Orientation")
			{
				auto op = std::dynamic_pointer_cast<LIST_PROPERTY>(p);
				if (op)
				{
					X.Orientation((winrt::Microsoft::UI::Xaml::Controls::Orientation)op->SelectedIndex);
				}
			}
		}

	}

	virtual void LoadProperties() override
	{
		properties.clear();
		if (1)
		{
			if (1)
			{
				std::shared_ptr<LIST_PROPERTY> op = std::make_shared<LIST_PROPERTY>();
				op->S = 1;
				op->g = L"StackPanel";
				op->n = L"Orientation";
				op->Items = { L"Vertical", L"Horizontal" };
				properties.push_back(op);

			}
		}

		if (1)
		{
			auto uip = CreatePropertiesFor(X.as<Panel>());
			for (auto& p : uip)
			{
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
		X = StackPanel();
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

		X.Orientation(winrt::Microsoft::UI::Xaml::Controls::Orientation::Vertical);
		X.Tag(box_value((long long)this));
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

std::shared_ptr<XITEM> CreateXItemStackPanel()
{
	return std::make_shared< ITEM_STACKPANEL>();
}
