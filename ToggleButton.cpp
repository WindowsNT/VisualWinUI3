#include "pch.h"
#include "property.hpp"

class ITEM_TOGGLEBUTTON : public XITEM
{
public:

	winrt::Microsoft::UI::Xaml::Controls::Primitives::ToggleButton X;
	virtual winrt::Windows::Foundation::IInspectable XX() override
	{
		return X;
	}
	ITEM_TOGGLEBUTTON()
	{
		ElementName = L"ToggleButton";
	}


	virtual void ApplyProperties()
	{
		try
		{

			for (auto& p : properties)
			{
				if (p->n == L"IsChecked")
				{
					auto op = std::dynamic_pointer_cast<LIST_PROPERTY>(p);
					if (op)
					{
						X.IsChecked(op->SelectedIndex);
					}
				}
				if (p->n == L"IsThreeState")
				{
					auto op = std::dynamic_pointer_cast<LIST_PROPERTY>(p);
					if (op)
					{
						X.IsThreeState(op->SelectedIndex);
					}
				}
			}

			ApplyPropertiesForContent(X.as<winrt::Microsoft::UI::Xaml::Controls::Primitives::ToggleButton>(), properties);
			ApplyPropertiesFor(X.as<Control>(), properties);
			ApplyPropertiesFor(X.as<UIElement>(), properties);
			ApplyPropertiesFor(X.as<FrameworkElement>(), properties);
		}
		catch (...)
		{

		}
	}


	virtual void LoadProperties() override
	{
		properties.clear();
		if (1)
		{
			auto uip = CreatePropertiesForContent(X.as<winrt::Microsoft::UI::Xaml::Controls::Primitives::ToggleButton>(), L"ToggleButton");
			for (auto& p : uip)
			{
				p->g = L"ToggleButton";
				properties.push_back(p);
			}
		}
		if (1)
		{
			std::shared_ptr<LIST_PROPERTY> op = std::make_shared<LIST_PROPERTY>();
			op->g = L"ToggleButton";
			op->n = L"IsChecked";
			op->Items = { L"False", L"True" };
			op->DefaultIndex = 0;
			properties.push_back(op);
		}
		if (1)
		{
			std::shared_ptr<LIST_PROPERTY> op = std::make_shared<LIST_PROPERTY>();
			op->g = L"ToggleButton";
			op->n = L"IsThreeState";
			op->Items = { L"False", L"True" };
			op->DefaultIndex = 0;
			properties.push_back(op);
		}

		AddPropertySet<Control>();
		AddPropertySet<FrameworkElement>();
		AddPropertySet<UIElement>();
	}

	virtual winrt::Microsoft::UI::Xaml::UIElement Create(int ForWhat, XITEM* par) override
	{
		X = winrt::Microsoft::UI::Xaml::Controls::Primitives::ToggleButton();
		the_par = par;
		if (properties.empty())
			LoadProperties();
		AddGridPropertiesIf<winrt::Microsoft::UI::Xaml::Controls::Primitives::ToggleButton>(par);

		if (ForWhat == 0)
		{
			AllTap(X);
		}

		X.Tag(box_value((long long)this));
		X.Content(winrt::box_value(L"ToggleButton"));
		return X;
	}




	void Select()
	{
		X.BorderBrush(SolidColorBrush(Colors::Red()));
		X.BorderThickness(ThicknessHelper::FromLengths(2.0, 2.0, 2.0, 2.0));
	}

	void Unselect()
	{
		X.BorderBrush(nullptr);
		X.BorderThickness(ThicknessHelper::FromLengths(0,0,0,0));
	}
};


std::shared_ptr<XITEM> CreateXItemToggleButton()
{
	return std::make_shared< ITEM_TOGGLEBUTTON>();
}
