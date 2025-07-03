#include "pch.h"
#include "property.hpp"

class ITEM_TEXTBLOCK : public XITEM
{
public:

	TextBlock X;
	virtual winrt::Windows::Foundation::IInspectable XX() override
	{
		return X;
	}
	ITEM_TEXTBLOCK()
	{
		ElementName = L"TextBlock";
	}


	virtual void ApplyProperties()
	{
		ApplyPropertiesForForeground(X.as<TextBlock>(), properties);
		ApplyPropertiesForFont(X.as<TextBlock>(), properties);
		ApplyPropertiesForText(X.as<TextBlock>(), properties);
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


			if (1)
			{
				auto uip1 = CreatePropertiesForFont(X.as<TextBlock>());
				for (auto& p : uip1)
				{
					p->g = L"TextBlock";
					properties.push_back(p);
				}
			}
			if (1)
			{
				auto uip1 = CreatePropertiesForForeground(X.as<TextBlock>());
				for (auto& p : uip1)
				{
					p->g = L"TextBlock";
					properties.push_back(p);
				}
			}


		}
		AddPropertySet<FrameworkElement>();
		AddPropertySet<UIElement>();
	}

	virtual winrt::Microsoft::UI::Xaml::UIElement Create(int ForWhat, XITEM* par) override
	{
		X = TextBlock();
		the_par = par;
		if (properties.empty())
			LoadProperties();
		AddGridPropertiesIf<TextBlock>(par);

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


std::shared_ptr<XITEM> CreateXItemTextBlock()
{
	return std::make_shared< ITEM_TEXTBLOCK>();
}
