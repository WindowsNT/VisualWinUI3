#include "pch.h"
#include "property.hpp"

class ITEM_HLBUTTON : public XITEM
{
public:

	HyperlinkButton X;
	virtual winrt::Windows::Foundation::IInspectable XX() override
	{
		return X;
	}
	ITEM_HLBUTTON()
	{
		ElementName = L"HyperlinkButton";
	}


	virtual void ApplyProperties()
	{
		try
		{
			for (auto& p : properties)
			{
				if (p->n == L"NavigateUri")
				{
					auto op = std::dynamic_pointer_cast<STRING_PROPERTY>(p);
					if (op)
					{
						X.NavigateUri(winrt::Windows::Foundation::Uri(op->value));
					}
				}
			}

			ApplyPropertiesForContent(X.as<HyperlinkButton>(), properties);
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
			std::shared_ptr<STRING_PROPERTY> op = std::make_shared<STRING_PROPERTY>();
			op->g = L"HyperlinkButton";
			op->n = L"NavigateUri";
			op->def = L"https://www.turbo-play.com";
			op->value = L"https://www.turbo-play.com";
			properties.push_back(op);

		}
		if (1)
		{
			auto uip = CreatePropertiesForContent(X.as<HyperlinkButton>(), L"HyperlinkButton");
			for (auto& p : uip)
			{
				p->g = L"HyperlinkButton";
				properties.push_back(p);
			}
		}
		AddPropertySet<Control>();
		AddPropertySet<FrameworkElement>();
		AddPropertySet<UIElement>();
	}

	virtual winrt::Microsoft::UI::Xaml::UIElement Create(int ForWhat, XITEM* par) override
	{
		X = HyperlinkButton();
		the_par = par;
		if (properties.empty())
			LoadProperties();
		AddGridPropertiesIf<HyperlinkButton>(par);

		if (ForWhat == 0)
		{
			AllTap(X);
		}

		X.Tag(box_value((long long)this));
		X.Content(winrt::box_value(L"HyperlinkButton"));
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


std::shared_ptr<XITEM> CreateXItemHLButton()
{
	return std::make_shared< ITEM_HLBUTTON>();
}
