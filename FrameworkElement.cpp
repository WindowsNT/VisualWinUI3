#include "pch.h"
#include "property.hpp"

void ApplyPropertiesFor(winrt::Microsoft::UI::Xaml::FrameworkElement e, std::vector <std::shared_ptr<PROPERTY>> props)
{
	if (!e)
		return;
	for (auto& p : props)
	{
		if (p->n == L"Name")
		{
			auto op = std::dynamic_pointer_cast<STRING_PROPERTY>(p);
			if (op && op->value.length())
			{
				e.Name(op->value);
			}
		}
		if (p->n == L"MinWidth")
		{
			auto op = std::dynamic_pointer_cast<DOUBLE_PROPERTY>(p);
			if (op && !std::isnan(op->value))
			{
				e.MinWidth(op->value);
			}
		}
		if (p->n == L"MinHeight")
		{
			auto op = std::dynamic_pointer_cast<DOUBLE_PROPERTY>(p);
			if (op && !std::isnan(op->value))
			{
				e.MinHeight(op->value);
			}
		}
		if (p->n == L"MaxWidth")
		{
			auto op = std::dynamic_pointer_cast<DOUBLE_PROPERTY>(p);
			if (op && !std::isnan(op->value))
			{
				e.MaxWidth(op->value);
			}
		}
		if (p->n == L"MaxHeight")
		{
			auto op = std::dynamic_pointer_cast<DOUBLE_PROPERTY>(p);
			if (op && !std::isnan(op->value))
			{
				e.MaxHeight(op->value);
			}
		}
	}
}


std::vector<std::shared_ptr<PROPERTY>> CreatePropertiesFor(winrt::Microsoft::UI::Xaml::FrameworkElement e)
{
	std::vector<std::shared_ptr<PROPERTY>> p;
	if (!e)
		return p;

	if (1)
	{
		std::shared_ptr<DOUBLE_PROPERTY> op = std::make_shared<DOUBLE_PROPERTY>();
		op->g = L"FrameworkElement";
		op->n = L"MaxHeight";
		op->mmin = 0.0;
		op->mmax = 10000;
		op->value = std::nan("");
		op->def = std::nan("");
		p.push_back(op);
	}
	if (1)
	{
		std::shared_ptr<DOUBLE_PROPERTY> op = std::make_shared<DOUBLE_PROPERTY>();
		op->g = L"FrameworkElement";
		op->n = L"MaxWidth";
		op->mmin = 0.0;
		op->mmax = 10000;
		op->value = std::nan("");
		op->def = std::nan("");
		p.push_back(op);
	}
	if (1)
	{
		std::shared_ptr<DOUBLE_PROPERTY> op = std::make_shared<DOUBLE_PROPERTY>();
		op->g = L"FrameworkElement";
		op->n = L"MinHeight";
		op->mmin = 0.0;
		op->mmax = 10000;
		op->value = std::nan("");
		op->def = std::nan("");
		p.push_back(op);
	}
	if (1)
	{
		std::shared_ptr<DOUBLE_PROPERTY> op = std::make_shared<DOUBLE_PROPERTY>();
		op->g = L"FrameworkElement";
		op->n = L"MinWidth";
		op->mmin = 0.0;
		op->mmax = 10000;
		op->value = std::nan("");
		op->def = std::nan("");
		p.push_back(op);
	}
	if (1)
	{
		std::shared_ptr<STRING_PROPERTY> op = std::make_shared<STRING_PROPERTY>();
		op->g = L"FrameworkElement";
		op->n = L"Name";
		op->value = e.Name();
		p.push_back(op);
	}

	return p;
}
