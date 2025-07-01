#include "pch.h"
#include "Item.h"
#include "Item.g.cpp"
#include "MainWindow.xaml.h"
#include "property.hpp"

extern std::map<HWND, winrt::Windows::Foundation::IInspectable> windows;

namespace winrt::VisualWinUI3::implementation
{
    void Item::Number0(double n)
    {
        _d0 = n;

        // Apply
        for (auto& wi : windows)
        {
			auto the_window = wi.second.as<winrt::VisualWinUI3::MainWindow>();

            // Find the MainPage for it
			auto tnv = the_window.Content().as<winrt::Microsoft::UI::Xaml::Controls::NavigationView>();
            if (!tnv)
                continue;
			
			auto fr = tnv.FindName(L"contentFrame").as<winrt::Microsoft::UI::Xaml::Controls::Frame>();
            if (!fr)
				continue;
            auto main_page = fr.Content().as<winrt::VisualWinUI3::MainPage>();
			if (!main_page)
                continue;
			
            // Find the item
            if (!SelectedItem)
                continue;

            for (auto& props : SelectedItem->properties)
            {
                if ((long long)props.get() == _PropertyX)
                {
					auto double_type = std::dynamic_pointer_cast<DOUBLE_PROPERTY>(props);
                    if (double_type)
                    {
                        if (double_type->value == _d0)
							return; // No change
                        double_type->value = _d0;

                    }
                    break;
                }
            }

			SelectedItem->ApplyProperties();
            


        }
        
    }

}


