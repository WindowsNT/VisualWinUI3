#pragma once
#include "Item.g.h"

namespace winrt::VisualWinUI3::implementation
{
    struct Item : ItemT<Item>
    {
        Item()
        {

        }
        long long _PropertyX = 0;
        int _type = 0;
        double _d0 = 0.0;
        double _d1 = 0.0;
		double _d2 = 0.0;
        std::wstring _n1;
        std::wstring _n2;
        // xitems
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::hstring> _xitems = single_threaded_observable_vector<winrt::hstring>();
        void xitems(winrt::Windows::Foundation::Collections::IObservableVector<winrt::hstring> v)
        {
            _xitems = v;
		}
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::hstring> xitems()
        {
            return _xitems;
		}


        hstring Name1()
        {
            return _n1.c_str();
        }
        hstring Name2()
        {
            return _n2.c_str();
        }
        int Type()
        {
            return _type;
		}
        double Number0()
        {
            return _d0;
		}
        double Number1()
        {
            return _d1;
		}
        double Number2()
        {
            return _d2;
        }
        long long PropertyX()
        {
            return _PropertyX;
		}
     

        void Name1(hstring n)
        {
            _n1 = n.c_str();
        }

        void Name2(hstring n)
        {
            _n2 = n.c_str();
        }
        void Type(int t)
        {
            _type = t;
		}
        void Number0(double n);
        void Number1(double n)
        {
            _d1 = n;
        }
        void Number2(double n)
        {
            _d2 = n;
		}
        void PropertyX(long long n)
        {
            _PropertyX = n;
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


        winrt::Windows::Foundation::Collections::IObservableVector<winrt::VisualWinUI3::Item> ComboItems();

    };
}
namespace winrt::VisualWinUI3::factory_implementation
{
    struct Item : ItemT<Item, implementation::Item>
    {
    };
}
