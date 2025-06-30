#pragma once
#include "Item.g.h"

namespace winrt::VisualWinUI3::implementation
{
    struct Item : ItemT<Item>
    {
        Item()
        {

        }
        std::wstring _n1;
        std::wstring _n2;
        std::wstring _src;
        hstring Name1()
        {
            return _n1.c_str();
        }
        hstring Name2()
        {
            return _n2.c_str();
        }
        hstring Source()
        {
            return _src.c_str();
        }

        void Name1(hstring n)
        {
            _n1 = n.c_str();
        }

        void Name2(hstring n)
        {
            _n2 = n.c_str();
        }
        void Source(hstring n)
        {
            _src = n.c_str();
        }

        bool Sel()
        {
            return 0;
        }
        void Sel(bool)
        {
        }


        winrt::Microsoft::UI::Xaml::Media::Brush ColorX()
        {
            auto col = winrt::Windows::UI::Color();
            col.A = 100;
            col.R = 255;
            if (Sel())
                col.A = 255;
            auto sb = winrt::Microsoft::UI::Xaml::Media::SolidColorBrush();
            sb.Color(col);
            return sb;
        }

        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
        {
            return m_propertyChanged.add(handler);
        }
        void PropertyChanged(winrt::event_token const& token) noexcept
        {
            m_propertyChanged.remove(token);
        }
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;


    };
}
namespace winrt::VisualWinUI3::factory_implementation
{
    struct Item : ItemT<Item, implementation::Item>
    {
    };
}
