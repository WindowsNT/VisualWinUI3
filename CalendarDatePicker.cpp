#include "pch.h"
#include "property.hpp"

class ITEM_CALENDARDATEPICKER : public XITEM
{
public:

	CalendarDatePicker X;
	virtual winrt::Windows::Foundation::IInspectable XX() override
	{
		return X;
	}
	ITEM_CALENDARDATEPICKER()
	{
		ElementName = L"CalendarDatePicker";
	}


	virtual void ApplyProperties()
	{
		try
		{

			for (auto& p : properties)
			{
				p;
			}

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
		AddPropertySet<Control>();
		AddPropertySet<FrameworkElement>();
		AddPropertySet<UIElement>();
	}

	virtual winrt::Microsoft::UI::Xaml::UIElement Create(int ForWhat, XITEM* par) override
	{
		X = CalendarDatePicker();
		the_par = par;
		if (properties.empty())
			LoadProperties();
		AddGridPropertiesIf<CheckBox>(par);

		if (ForWhat == 0)
		{
			AllTap(X);
		}

		X.Tag(box_value((long long)this));
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


std::shared_ptr<XITEM> CreateXItemCalendarDatePicker()
{
	return std::make_shared< ITEM_CALENDARDATEPICKER>();
}
