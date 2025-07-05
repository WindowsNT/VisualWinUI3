#include "pch.h"
#include "property.hpp"

class ITEM_CHECKBOX : public XITEM
{
public:

	CheckBox X;
	virtual winrt::Windows::Foundation::IInspectable XX() override
	{
		return X;
	}
	ITEM_CHECKBOX()
	{
		ElementName = L"CheckBox";
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

			ApplyPropertiesForContent(X.as<CheckBox>(), properties);
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
			auto uip = CreatePropertiesForContent(X.as<CheckBox>(), L"CheckBox");
			for (auto& p : uip)
			{
				p->g = L"CheckBox";
				properties.push_back(p);
			}
		}
		if (1)
		{
			std::shared_ptr<BOOL_PROPERTY> op = std::make_shared<BOOL_PROPERTY>();
			op->g = L"CheckBox";
			op->n = L"IsChecked";
			op->DefaultIndex = 0;
			properties.push_back(op);
		}
		if (1)
		{
			std::shared_ptr<BOOL_PROPERTY> op = std::make_shared<BOOL_PROPERTY>();
			op->g = L"CheckBox";
			op->n = L"IsThreeState";
			op->DefaultIndex = 0;
			properties.push_back(op);
		}

		AddPropertySet<Control>();
		AddPropertySet<FrameworkElement>();
		AddPropertySet<UIElement>();
	}

	virtual winrt::Microsoft::UI::Xaml::UIElement Create(int ForWhat, XITEM* par) override
	{
		X = CheckBox();
		the_par = par;
		if (properties.empty())
			LoadProperties();
		AddGridPropertiesIf<CheckBox>(par);

		if (ForWhat == 0)
		{
			AllTap(X);
		}

		X.Tag(box_value((long long)this));
		X.Content(winrt::box_value(L"CheckBox"));
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


std::shared_ptr<XITEM> CreateXItemCheckBox()
{
	return std::make_shared< ITEM_CHECKBOX>();
}
