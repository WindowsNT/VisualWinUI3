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

std::vector<std::shared_ptr<PROPERTY>> CreatePropertiesFor(winrt::Microsoft::UI::Xaml::UIElement e);
void ApplyPropertiesFor(winrt::Microsoft::UI::Xaml::UIElement e, std::vector <std::shared_ptr<PROPERTY>> props);
std::vector<std::shared_ptr<PROPERTY>> CreatePropertiesFor(winrt::Microsoft::UI::Xaml::FrameworkElement e);
void ApplyPropertiesFor(winrt::Microsoft::UI::Xaml::FrameworkElement e, std::vector <std::shared_ptr<PROPERTY>> props);
void XMLPropertiesFor(XML3::XMLElement& ee, std::vector <std::shared_ptr<PROPERTY>> props);


class XITEM
{
public:

	std::wstring ElementName; // Say, "StackPanel"
	std::vector<std::shared_ptr<PROPERTY>> properties;
	std::vector<std::shared_ptr<XITEM>> children;
	virtual winrt::Microsoft::UI::Xaml::UIElement Create() = 0;
	virtual void ApplyProperties() = 0;

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
			using namespace winrt::Microsoft::UI::Xaml::Media;
			using namespace winrt;
			using namespace Microsoft::UI::Xaml;
			using namespace Microsoft::UI::Xaml::Controls;
			using namespace Microsoft::UI::Xaml::Media;
			using namespace Windows::UI;

			ApplyPropertiesFor(X.as<UIElement>(), properties);
			ApplyPropertiesFor(X.as<FrameworkElement>(), properties);
		}

		virtual winrt::Microsoft::UI::Xaml::UIElement Create() override
		{
			using namespace winrt::Microsoft::UI::Xaml::Media;
			using namespace winrt;
			using namespace Microsoft::UI::Xaml;
			using namespace Microsoft::UI::Xaml::Controls;
			using namespace Microsoft::UI::Xaml::Media;
			using namespace Windows::UI;

			properties.clear();
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

			X.Tapped([](winrt::Windows::Foundation::IInspectable t, winrt::Windows::Foundation::IInspectable)
				{
					GenericTap(t);
				});

			X.Tag(box_value((long long)this));
			X.BorderBrush(SolidColorBrush(Colors::Blue()));
			winrt::Microsoft::UI::Xaml::Thickness th = { 1, 1, 1, 1 };
			X.BorderThickness(th);
			return X;
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
		using namespace winrt::Microsoft::UI::Xaml::Media;
		using namespace winrt;
		using namespace Microsoft::UI::Xaml;
		using namespace Microsoft::UI::Xaml::Controls;
		using namespace Microsoft::UI::Xaml::Media;
		using namespace Windows::UI;

		ApplyPropertiesFor(X.as<UIElement>(), properties);
		ApplyPropertiesFor(X.as<FrameworkElement>(), properties);
	}

	virtual winrt::Microsoft::UI::Xaml::UIElement Create() override
	{
		using namespace winrt::Microsoft::UI::Xaml::Media;
		using namespace winrt;
		using namespace Microsoft::UI::Xaml;
		using namespace Microsoft::UI::Xaml::Controls;
		using namespace Microsoft::UI::Xaml::Media;
		using namespace Windows::UI;

		properties.clear();
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

		X.Tapped([](winrt::Windows::Foundation::IInspectable t, winrt::Windows::Foundation::IInspectable)
			{
				GenericTap(t);
			});

		X.Tag(box_value((long long)this));
		X.Content(winrt::box_value(L"Button"));
		return X;
	}
};

inline std::shared_ptr<XITEM> SelectedItem;
