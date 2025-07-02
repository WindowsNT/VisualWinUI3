#pragma once

class SERIALIZABLE
{
public:

	virtual void Ser(XML3::XMLElement& el) = 0;
	virtual void Unser(XML3::XMLElement& el) = 0;
};


class PROPERTY : public SERIALIZABLE
{

public:
	std::wstring g;
	std::wstring n;
	std::wstring xmln;
	virtual void Ser(XML3::XMLElement& el) override
	{
		el.vv("g").SetValue(g);
		el.vv("n").SetValue(n);
		el.vv("x").SetValue(xmln);

	}

	virtual void Unser(XML3::XMLElement& el) override
	{
		g = el.vv("g").GetWideValue();
		n = el.vv("n").GetWideValue();
		xmln = el.vv("x").GetWideValue();
	}

};


enum PROPERTY_TYPE
{
	PT_STRING,
	PT_INT,
	PT_DOUBLE,
	PT_LIST,
};

class STRING_PROPERTY : public PROPERTY
{
public:
	std::wstring value;
	std::wstring def = L"";
	virtual void Ser(XML3::XMLElement& el) override
	{
		PROPERTY::Ser(el);
		el.vv("v").SetValue(value);
		el.vv("def").SetValue(def);
	}
	virtual void Unser(XML3::XMLElement& el) override
	{
		PROPERTY::Unser(el);
		value = el.vv("v").GetWideValue();
		def = el.vv("def").GetWideValue();
	}
};

class INT_PROPERTY : public PROPERTY
{
	public:
	long long value = 0;
	long long def = 0;
	long long mmin = -1000;
	long long mmax = 1000;
	virtual void Ser(XML3::XMLElement& el) override
	{
		PROPERTY::Ser(el);
		el.vv("v").SetValueLongLong(value);
		el.vv("def").SetValueLongLong(def);
		el.vv("min").SetValueLongLong(mmin);
		el.vv("max").SetValueLongLong(mmax);
	}
	virtual void Unser(XML3::XMLElement& el) override
	{
		PROPERTY::Unser(el);
		value = el.vv("v").GetValueLongLong();
		def = el.vv("def").GetValueLongLong(0);
		mmin = el.vv("min").GetValueLongLong(-1000);
		mmax = el.vv("max").GetValueLongLong(1000);
	}
};

class LIST_PROPERTY : public PROPERTY
{
public:

	std::vector<std::wstring> Items;
	size_t SelectedIndex = 0;
	size_t DefaultIndex = 0;

	virtual void Ser(XML3::XMLElement& el) override
	{
		PROPERTY::Ser(el);
		// Serialize list items here if needed
		el.vv("s").SetValueULongLong(SelectedIndex);
		el.vv("d").SetValueULongLong(DefaultIndex);
	}


	virtual void Unser(XML3::XMLElement& el) override
	{
		PROPERTY::Unser(el);
		// Deserialize list items here if needed
		SelectedIndex = el.vv("s").GetValueULongLong(0);
		DefaultIndex = el.vv("d").GetValueULongLong(0);
	}
};

class DOUBLE_PROPERTY : public PROPERTY
{
	public:
	double def = 0.0;
	double value = 0.0;
	double mmin = 0.0;
	double mmax = 1.0;
	virtual void Ser(XML3::XMLElement& el) override
	{
		PROPERTY::Ser(el);
		el.vv("v").SetValueDouble(value);
		el.vv("def").SetValueDouble(def);
		el.vv("min").SetValueDouble(mmin);
		el.vv("max").SetValueDouble(mmax);
	}
	virtual void Unser(XML3::XMLElement& el) override
	{
		PROPERTY::Unser(el);
		value = el.vv("v").GetValueDouble();
		def = el.vv("def").GetValueDouble(0.0);
		mmin = el.vv("min").GetValueDouble(0);
		mmax = el.vv("max").GetValueDouble(1);
	}
};

void ApplyPropertiesFor(winrt::Microsoft::UI::Xaml::UIElement e, std::vector <std::shared_ptr<PROPERTY>> props);
void ApplyPropertiesFor(winrt::Microsoft::UI::Xaml::FrameworkElement e, std::vector <std::shared_ptr<PROPERTY>> props);

using namespace winrt::Microsoft::UI::Xaml::Media;
using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Media;
using namespace Windows::UI;

template <typename T>
void ApplyPropertiesForText(T e, std::vector <std::shared_ptr<PROPERTY>> props)
{
	for (auto& p : properties)
	{
		if (p->n == L"Text")
		{
			auto op = std::dynamic_pointer_cast<STRING_PROPERTY>(p);
			if (op)
			{
				e.Text(op->value);
			}
		}
	}
}
template <typename T>
void ApplyPropertiesForContent(T e, std::vector <std::shared_ptr<PROPERTY>> properties)
{
	for (auto& p : properties)
	{
		if (p->n == L"Content")
		{
			auto op = std::dynamic_pointer_cast<STRING_PROPERTY>(p);
			if (op)
			{
				e.Content(winrt::box_value(op->value));
			}
		}
	}
}


std::vector<std::shared_ptr<PROPERTY>> CreatePropertiesFor(winrt::Microsoft::UI::Xaml::UIElement e);
std::vector<std::shared_ptr<PROPERTY>> CreatePropertiesFor(winrt::Microsoft::UI::Xaml::FrameworkElement e);
template <typename T>
std::vector<std::shared_ptr<PROPERTY>> CreatePropertiesForText(T e)
{
	std::vector<std::shared_ptr<PROPERTY>> p;
	if (!e)
		return p;

	if (1)
	{
		std::shared_ptr<STRING_PROPERTY> op = std::make_shared<STRING_PROPERTY>();
		op->n = L"Text";
		op->value = e.Text();
		op->def = L"";
		p.push_back(op);
	}
	return p;
}
template <typename T>
std::vector<std::shared_ptr<PROPERTY>> CreatePropertiesForContent(T e,const wchar_t*defv)
{
	std::vector<std::shared_ptr<PROPERTY>> p;
	if (!e)
		return p;

	if (1)
	{
		std::shared_ptr<STRING_PROPERTY> op = std::make_shared<STRING_PROPERTY>();
		op->n = L"Content";
		if (defv)
			op->value = defv;
		try
		{
			auto cont = e.Content();
			op->value = winrt::unbox_value<winrt::hstring>(cont);
		}
		catch (...)
		{
		}
		p.push_back(op);
	}
	return p;
}


void XMLPropertiesFor(XML3::XMLElement& ee, std::vector <std::shared_ptr<PROPERTY>> props);
void LoadXMLPropertiesfor(XML3::XMLElement& ee, std::vector <std::shared_ptr<PROPERTY>> props);


class XITEM : public SERIALIZABLE
{
public:

	std::wstring ElementName; // Say, "StackPanel"
	std::vector<std::shared_ptr<PROPERTY>> properties;
	std::vector<std::shared_ptr<XITEM>> children;
	virtual winrt::Microsoft::UI::Xaml::UIElement Create()
	{
		return nullptr;
	}
	virtual void LoadProperties()
	{

	}
	virtual void ApplyProperties()
	{

	}

	virtual XML3::XMLElement SaveEl()
	{
		XML3::XMLElement ee;
		ee.SetElementName(XML3::XMLU(ElementName.c_str()).bc());
		XMLPropertiesFor(ee, properties);

		for (auto& ch : children)
		{
			XML3::XMLElement& eee = ee.AddElement(XML3::XMLU(ch->ElementName.c_str()).bc());
			XMLPropertiesFor(eee, ch->properties);
		}
		return ee;
	}

	virtual void Ser(XML3::XMLElement& el) override
	{
		el.SetElementName(ElementName.c_str());
		XMLPropertiesFor(el, properties);
		for (auto& ch : children)
		{
			XML3::XMLElement& eee = el.AddElement(XML3::XMLU(ch->ElementName.c_str()).bc());
			ch->Ser(eee);
		}
	}
	virtual void Unser(XML3::XMLElement& el) override;

	virtual 	void Select()
	{
	}

	virtual 	void Unselect()
	{
	}

};

void GenericTap(winrt::Windows::Foundation::IInspectable);



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
					properties.push_back(op);

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
		ApplyPropertiesFor(X.as<UIElement>(), properties);
		ApplyPropertiesFor(X.as<FrameworkElement>(), properties);
	}


	virtual void LoadProperties() override
	{
		properties.clear();
		if (1)
		{
			auto uip = CreatePropertiesForContent(X.as<Button>(),L"Button");
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

inline std::shared_ptr<XITEM> SelectedItem;


inline void XITEM::Unser(XML3::XMLElement& el)
{
	children.clear();
	LoadProperties();
	LoadXMLPropertiesfor(el, properties);
	for (auto& e : el)
	{
		auto el2 = e.GetElementName();
		std::shared_ptr<XITEM> ch;
		if (el2 == "StackPanel")	ch = std::make_shared<ITEM_STACKPANEL>();
		if (el2 == "Button")	ch = std::make_shared<ITEM_BUTTON>();
		if (!ch)
			continue;
		ch->Unser(e);
		children.push_back(ch);
	}
}
