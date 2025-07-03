#include "pch.h"
#include "property.hpp"

class ITEM_TEXTBOX : public XITEM
{
public:

	TextBox X;
	virtual winrt::Windows::Foundation::IInspectable XX() override
	{
		return X;
	}
	ITEM_TEXTBOX()
	{
		ElementName = L"TextBox";
	}


	virtual void ApplyProperties()
	{
		ApplyPropertiesForText(X.as<TextBox>(), properties);
		ApplyPropertiesFor(X.as<Control>(), properties);
		ApplyPropertiesFor(X.as<UIElement>(), properties);
		ApplyPropertiesFor(X.as<FrameworkElement>(), properties);
	}


	virtual void LoadProperties() override
	{
		properties.clear();
		if (1)
		{
			auto uip = CreatePropertiesForText<TextBox>(X.as<TextBox>(), L"TextBox");
			for (auto& p : uip)
			{
				p->g = L"TextBox";
				properties.push_back(p);
			}
		}
		AddPropertySet<Control>();
		AddPropertySet<FrameworkElement>();
		AddPropertySet<UIElement>();
	}

	virtual winrt::Microsoft::UI::Xaml::UIElement Create(int ForWhat) override
	{
		X = TextBox();
		if (properties.empty())
			LoadProperties();

		if (ForWhat == 0)
		{
			AllTap(X);
		}
		X.Tag(box_value((long long)this));
		if (ForWhat == 0)
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


std::shared_ptr<XITEM> CreateXItemTextBox()
{
	return std::make_shared< ITEM_TEXTBOX>();
}
