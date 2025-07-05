#include "pch.h"
#include "property.hpp"

class ITEM_RATINGCONTROL : public XITEM
{
public:

	RatingControl X;
	virtual winrt::Windows::Foundation::IInspectable XX() override
	{
		return X;
	}
	ITEM_RATINGCONTROL()
	{
		ElementName = L"RatingControl";
	}


	virtual void ApplyProperties()
	{
		for(auto& p : properties)
			{
			if (p->n == L"MaxRating")
			{
				auto op = std::dynamic_pointer_cast<DOUBLE_PROPERTY>(p);
				if (op)
				{
					X.MaxRating((int)op->value);
				}
			}
			if (p->n == L"Value")
			{
				auto op = std::dynamic_pointer_cast<DOUBLE_PROPERTY>(p);
				if (op)
				{
					X.Value(op->value);
				}
			}
			if (p->n == L"IsClearEnabled")
			{
				auto op = std::dynamic_pointer_cast<LIST_PROPERTY>(p);
				if (op)
				{
					X.IsClearEnabled(op->SelectedIndex);
				}
			}
		}
		ApplyPropertiesFor(X.as<Control>(), properties);
		ApplyPropertiesFor(X.as<UIElement>(), properties);
		ApplyPropertiesFor(X.as<FrameworkElement>(), properties);
	}


	virtual void LoadProperties() override
	{
		properties.clear();


		if (1)
		{
			std::shared_ptr<BOOL_PROPERTY> op = std::make_shared<BOOL_PROPERTY>();
			op->g = L"RatingControl";
			op->n = L"IsClearEnabled";
			op->DefaultIndex = 0;
			properties.push_back(op);
		}
		if (1)
		{
			std::shared_ptr<DOUBLE_PROPERTY> op = std::make_shared<DOUBLE_PROPERTY>();
			op->g = L"RatingControl";
			op->n = L"MaxRating";
			op->mmin = 1;
			op->mmax = 100;
			op->smallchange = 1;
			op->largechange = 2;
			op->value = X.MaxRating();
			op->def = 5;
			properties.push_back(op);
		}
		if (1)
		{
			std::shared_ptr<DOUBLE_PROPERTY> op = std::make_shared<DOUBLE_PROPERTY>();
			op->g = L"RatingControl";
			op->n = L"Value";
			op->mmin = 1;
			op->mmax = 100;
			op->smallchange = 0.5;
			op->largechange = 0.5;
			op->value = X.Value();
			op->def = X.Value();
			properties.push_back(op);
		}

		AddPropertySet<Control>();
		AddPropertySet<FrameworkElement>();
		AddPropertySet<UIElement>();
	}

	virtual winrt::Microsoft::UI::Xaml::UIElement Create(int ForWhat, XITEM* par) override
	{
		X = RatingControl();
		the_par = par;
		if (properties.empty())
			LoadProperties();
		AddGridPropertiesIf<RatingControl>(par);

		if (ForWhat == 0)
		{
			AllTap(X);
		}
		X.Tag(box_value((long long)this));
		X.IsReadOnly(false);
		return X;
	}




	void Select()
	{
	}

	void Unselect()
	{
	}
};


std::shared_ptr<XITEM> CreateXItemRatingControl()
{
	return std::make_shared< ITEM_RATINGCONTROL>();
}
