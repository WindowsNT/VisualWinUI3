#include "pch.h"
#include "property.hpp"

using namespace winrt::Microsoft::UI::Xaml::Controls;
class ITEM_STACKPANEL : public XITEM
{
public:

	StackPanel X;
	virtual winrt::Windows::Foundation::IInspectable XX() override
	{
		return X;
	}

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
				op->g = L"StackPanel";
				op->n = L"Orientation";
				op->Items = { L"Vertical", L"Horizontal" };
				op->DefaultIndex = 0;
				properties.push_back(op);

			}
		}

		AddPropertySet<Panel>();
		AddPropertySet<FrameworkElement>();
		AddPropertySet<UIElement>();
	}

	virtual winrt::Microsoft::UI::Xaml::UIElement Create(int ForWhat) override
	{
		X = StackPanel();
		if (properties.empty())
			LoadProperties();

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

std::shared_ptr<XITEM> CreateXItemStackPanel()
{
	return std::make_shared< ITEM_STACKPANEL>();
}
